//checking whether a set of nodes leaves itself is a common enough tasks to include here
//for example, if you give a connected component, visits_outside is a sink check

#ifndef VISIT_OUTSIDEN
#define VISIT_OUTSIDEN
#include<unordered_map>
#include<unordered_set>

//true if node set not a sink
template<typename T>
bool visits_outside(int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, std::unordered_set<int>& node_set) {
 
  if (node_set.size() == 0) return false;
  
  bool left_set=false;

   for (int i : node_set) {

    for (const auto& kvp : edges[i]) {
      if (!( node_set.find(kvp.first) != node_set.end() ) ) return true;
        
    }
  }
  

  return false;

}

#endif //VISIT_OUTSIDE