#include "graph.h"
#include "min_heap.h"

//find the MST of a graph, return as vector of edge pairs
//uses min heap to determine which vertex to include next 
std::vector<std::pair<int,int>> Graph::prims() {

  MinHeap my_heap;
  std::vector<double> mstSet(n,false);
  std::vector<int> parent(n,-1);


  for (int i = 0; i < n; i++) {
    my_heap.insert(i,INF);

  }
  my_heap.decrease_key(0,0);
  parent[0]=0;

  for (int count = 0; count < n-1; count++) { //for each vertex we want to add to the MST
    int u = my_heap.delete_min();
    mstSet[u]=true;

    //kvp=key value pair (a std::pair)
    //.first is outgoing edge
    //.second is weight
    for (const auto& kvp : weights[u]) {
    // std::cout << "with incoming " << u << ", " << "kvp: " << kvp.first << " " << kvp.second << std::endl;
      if (!mstSet[kvp.first]) {
        bool changed_val = my_heap.decrease_key(kvp.first,kvp.second);
        if (changed_val) {
          parent[kvp.first]=u;
        }
        
      }
    }
  }

  std::vector<std::pair<int,int>> mst_edges;
  mst_edges.reserve(n-1);
  for (int i =1 ;i < n; i++) {
    mst_edges.push_back(std::make_pair(i,parent[i]));

  }
  return mst_edges;
  
}
