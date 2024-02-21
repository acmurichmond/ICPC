//https://open.kattis.com/problems/maxflow
//solves maxflow problem here

#include<iostream>
#include<vector>
#include<unordered_map>
#include<deque>
//Python print("hi",end="") #to avoid newline

//given a start node s and end node t, and parent vector parent, write out the explicit path from s to t in path
void create_path(std::vector<int>& parent, int s, int t, std::deque<int>& path) {
  path.push_front(t);
  while (t != s) {
    t = parent[t];
    path.push_front(t);
  }
  
}
//update path with bfs
//returns true if path updated, false otherwise
template<typename T>
bool bfs_mf(int n, std::unordered_map<int, std::unordered_map<int, T> >& edges, int s, int t, std::deque<int>& path) {

  std::vector<bool> visited(n,false);
  std::vector<int> parent(n,-1);


  std::deque<int> q;
  q.push_back(s);

  while (q.size() > 0) {
    int v = q.front(); //note that bfs takes from front of q, not back like dfs
    q.pop_front();

    // std::cout << "visiting " << v << std::endl;
    // std::cout << "printing VISITED arr: ";
    // for (int i = 0; i < visited.size(); i++) {
    //   std::cout << visited[i] << " ";
    // }
    // std::cout << std::endl;
  
    if (!visited[v]) {
    //  std::cout << v << " not visited yet." <<std::endl;
    
      visited[v]=true;

      //for each neighbor
      for (const auto& kvp : edges[v]) {
        // std::cout << "Considering visit to " << kvp.first << std::endl;
        // std::cout << "printing visited arr: ";
        // for (int i = 0; i < visited.size(); i++) {
        //   std::cout << visited[i] << " ";
        // }
        // std::cout << std::endl;
        //if we haven't visited it yet and edge not saturated
        if (!visited[kvp.first] && kvp.second > 0) {
          
          q.push_back(kvp.first);
          parent[kvp.first]=v;
          //if we have reached our goal, return the path
          if (kvp.first == t) {
          //  std::cout << "reached the goal!" << std::endl;
            create_path(parent,s,t,path);
            return true;

          }
         
        
        }
      }

    }
    // else {
    //   std::cout << "Choosing not to visit " << v << std::endl;
    // }
  }
  //std::cout << "queue empty " << std::endl;

  return false;


}

//R is residuals map 
//by returning this, we get info about what edges were used
template<typename T>
int maxflow(int n, std::unordered_map<int, std::unordered_map<int, T> >& edges, std::unordered_map<int, std::unordered_map<int, T> >& R, int s, int t, int INF) {

 // std::cout << "Entered max flow" << std::endl;


  //R is residuals graph edge weights
  
  //copy edges into R
  for (const auto& kvp1 : edges) {
    for (const auto& kvp2 : kvp1.second) {
      R[kvp1.first][kvp2.first]=kvp2.second;
    }
  }


// std::cout << "printing residuals " << std::endl;
  // for (const auto& kvp1 : R) {
  //   std::cout << kvp1.first << ": ";
  //   for (const auto& kvp2 : kvp1.second) {
  //     std::cout << kvp2.first << "(" << kvp2.second << ")" << " ";

  //   }
  //   std::cout << std::endl;
  // }

//  std::cout << "defined residuals " << std::endl;
  

  int flow = 0;
  std::deque<int> path_deque;
  int path_len = 0;
  while (bfs_mf(n,R,s,t,path_deque)) {
    //std::cout << "bfs ING " << std::endl;
    int F = INF;
    //note the iterator arithmetic here! 
    for (auto i = path_deque.begin(); (i+1) != path_deque.end(); i += 1) {
      F = std::min(R[*i][*(i+1)],F);

    }
    
    flow += F;
    for (auto i = path_deque.begin(); i+1 != path_deque.end(); i++) {
      int v = *i;
      int u = *(i+1);
      R[v][u] -= F;
      R[u][v] += F;
    }
    path_deque.clear(); //clear out deque
  

  }
  return flow;

}