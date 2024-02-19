//bfs function

#ifndef BFS
#define BFS
#include<deque> 
#include<unordered_map>
#include<unordered_set> 
#include<vector>

//do bfs
//returns a set of all the nodes visited
//start is the start vertex
//writes node depths into depths (which is assumed to start at INF)
template<typename T>
std::unordered_set<int> bfs(const int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, std::vector<int> starts,std::vector<int>& depths) {

  std::vector<bool> visited(n,false);

  std::deque<int> stack;

  for (int i : starts) {
    stack.push_back(i);
    depths[i]=0;
  }
  std::unordered_set<int> visited_nodes;

  while (stack.size() > 0) {
    int s = stack.front(); //note that bfs takes from front of stack, not back like dfs
    stack.pop_front();
    visited_nodes.insert(s);
  
    if (!visited[s]) {
    
      visited[s]=true;

      //for each neighbor
      for (const auto& kvp : edges[s]) {
        //if we haven't visited it yet
        if (!visited[kvp.first]) {
          
          stack.push_back(kvp.first);
          depths[kvp.first] = std::min(depths[s] + 1,depths[kvp.first]);
        
        }
      }

    }
  }

  return visited_nodes;

}

#endif