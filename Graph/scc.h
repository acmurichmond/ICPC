#ifndef SCC
#define SCC

#include "graph.h"
#include "dfs.h"
#include<algorithm> //for sort

//warning: scc will necessarily reset visited and post before running!
//scc returns a list of connected components, in the form of sets. 
//By construction, the sets are ordered from sources to sinks
std::vector<std::unordered_set<int>> Graph::scc() {
  
  order_num=0;
  for (int i = 0; i < n; i++) {
    nodes[i].is_post_node=false;
    nodes[i].resolved_post_node=false;
    nodes[i].visited=false;
    nodes[i].pre=-1;
    nodes[i].post=-1;
  }
 
  int star_node=0;
  while (order_num < 2*n) {
    if (star_node >= n) {
      std::cout << "Error star_node exceeded bound " << std::endl;
      exit(7);
    }
    dfs(star_node,false,true,false);
    star_node+=1;
  }
  std::vector<int> sorted_nodes(n);
  for (int i = 0; i < n; i++) {
    sorted_nodes[i]=i;
  }
  std::sort(sorted_nodes.begin(),sorted_nodes.end(), [&] (int a, int b) {return nodes[a].post > nodes[b].post;});

  std::vector<std::unordered_set<int>> scc_order;

  for (int i = 0; i < n; i++) {
    nodes[i].is_post_node=false;
    nodes[i].resolved_post_node=false;
    nodes[i].visited=false;
  }
  
  
  for (int i = 0; i < n; i++) {
    int node = sorted_nodes[i];
    if (!nodes[node].visited) {
      scc_order.push_back(dfs(node,true,false,false));
    }
  }
  return scc_order;

}


#endif