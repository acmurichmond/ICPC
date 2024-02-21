#ifndef DFSN
#define DFSN

#include<deque>
#include<unordered_map>
#include<unordered_set>

//do dfs
//by default, vertices for graph are integers 0-(n-1), edges is hashmap of hashmap of weights
//returns a set of all the nodes visited
//start is the start vertex
//T is type of weight (int or float)
//WARNING: not directly tested (dfs code in bellman ford, scc was tested though)
template<typename T> 
std::unordered_set<int> dfs(const int n, const std::unordered_map<int,std::unordered_map<int,T> >& edges, int start) {

  std::vector<bool> visited(n,false);
  
  std::deque<int> stack; //stores our dfs stack
  stack.push_back(start);
  std::unordered_set<int> visited_nodes; //stores all the nodes we visit during the dfs

  while (stack.size() > 0) {
    int s = stack.back(); //we pop from back of stack
    stack.pop_back();
    visited_nodes.insert(s);
   
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
  return visited_nodes;
}

#endif //DFS