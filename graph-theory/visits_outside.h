//checking whether a set of nodes leaves itself is a common enough tasks to include here
//for example, if you give a connected component, visits_outside is a sink check

#ifndef VISIT_OUTSIDE
#define VISIT_OUTSIDE
#include "graph.h"
#include<deque>

//true if does leave the node set
//reverse -- if true, use the reverse graph
//warning: relies on vo_mark starting off false
//we don't set vo_mark to false because this takes n steps, which can be costly on repeated runs
bool Graph::visits_outside(std::unordered_set<int> node_set, bool reverse=false, bool set_mark_false=false) {
 
  if (node_set.size() == 0) return false;
  
  if (set_mark_false) {
    for (int i = 0; i < n; i++) nodes[i].vo_mark=false; 
  }
  
  std::deque<int> stack;
  for (int i : node_set) nodes[i].vo_mark=true;
 
  std::unordered_map<int,std::unordered_set<int>>* my_edges;

  //use reverse boolean to determine which edge set to use
  if (reverse) my_edges=&rev_edges;
  else my_edges=&edges;
  
  bool left_set=false;

   for (int i : node_set) {
    for (int node : (*my_edges)[i]) {
      if (!nodes[node].vo_mark) {
        for (int j : node_set) nodes[i].vo_mark=false;
        return true;
        
        
      } 
    }
  }
  for (int j : node_set) nodes[j].vo_mark=false;

  return false;

}

#endif //VISIT_OUTSIDE