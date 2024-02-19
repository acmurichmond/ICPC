#ifndef BELL
#define BELL
#include<limits>
#include<unordered_map>
#include<vector>
#include<unordered_set>
#include<deque>


//helper dfs for bellman ford, for finding all of the negative inf cycles
//marks all nodes visited with neginf 
template<typename T> 
void bellman_dfs(const int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, int start,std::vector<bool>& visited, std::vector<T>& dist, T NEG_INF) {

  std::deque<int> stack; //stores our dfs stack
  stack.push_back(start);

  while (stack.size() > 0) {
    int s = stack.back(); //we pop from back of stack
    stack.pop_back();
    dist[s]=NEG_INF;
   
    //if we haven't yet visited this node
    if (! visited[s]) {
      visited[s]=true;
      //for each neighbor
      for (const auto& kvp : edges[s]) { //kvp = key value pair
        //if we haven't visited it yet
        if (!visited[kvp.first]) stack.push_back(kvp.first);

      }
    }
  }
 
}

//returns vector of shortest path from s to all other vertices
//if any of these weights is numeric limits min, then there is a negative weight cycle
//n : # of vertices
//s : start vertex
//T: distance type (int, long long, or float)
template <typename T>
std::vector<T> bellman_ford(const int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, int s, T INF, T NEG_INF) {

  std::vector<T> dist(n,std::numeric_limits<T>::max());
  
  dist[s]=0;

  bool update_made=true;

  for (int i  = 0; i < n-1; i++) {
    update_made=false;
    //for each edge
    for (int j = 0; j < n; j++) {
      for (const auto& kvp : edges[j]) { //kvp = key value pair
        if (dist[j] != INF && dist[j] + kvp.second < dist[kvp.first]) {
          dist[kvp.first]=dist[j]+kvp.second;
          update_made=true;
        }


      }
    }
    //if we did not make any shortest path updates this round, we can stop early (Dasgupta mentions, Algorithms p. 118)
    if (update_made==false) {
      break;
    }
  }

  bool any_neg = false;
  

  for (int j = 0; j < n; j++) {
    for (const auto& kvp : edges[j]) { 
      if ((dist[j] != INF && dist[j] + kvp.second < dist[kvp.first]) || dist[j]==NEG_INF) {
        dist[kvp.first]= NEG_INF;
        any_neg=true;
      }
    }
  }


  if (any_neg) {
    std::vector<bool> visited(n,false);

    //all nodes reachable from a NEG_INF node are NEG_INF
    for (int i = 0; i < n; i++) {
      if (dist[i] == NEG_INF && !visited[i]) {
        //TODO could do bfs instead here (but this works)
        bellman_dfs(n,edges,i,visited,dist,NEG_INF); //mark all visited nodes with negative infinity
       
      }
    }

  }
  return dist;
  
}


#endif