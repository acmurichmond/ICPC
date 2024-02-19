#include<unordered_set> 
#include<unordered_map>
#include<queue>
#include<deque>
#include <unistd.h> //TODO what for?

#include "min_heap.h"

template<typename T>
struct DijNode {
  int id;
  T dist;
  bool valid;
  std::vector<int> parents;
  bool resolved;
  DijNode(int id,T dist) : id(id),dist(dist),valid(true),resolved(false) {
    parents=std::vector<int>();
  }

  DijNode() {}
  
};
//we assume dists is reset to infinity at the start
template<typename T>
void dijkstra(const int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, int start,std::vector<T>& dists,std::vector<std::vector<int>>& parents, T INF) {

  MinHeap<T> my_heap;
  std::unordered_map<int,DijNode<T>> dij_nodes;
  for (int i = 0; i < n; i++) {
    dij_nodes[i] = DijNode<T>(i,INF);
  }

  for (int i = 0; i < n; i++) {
    my_heap.insert(i,dij_nodes[i].dist);
  }

  dij_nodes[start].dist=0;
  my_heap.decrease_key(start,0);

 //my_heap.print();

  
  while (!my_heap.empty()) {
 
    DijNode<T>& a = dij_nodes[my_heap.delete_min()];


    dists[a.id]=a.dist; //write in the answer
    for (int i = 0; i < a.parents.size(); i++) {
      parents[a.id].push_back(a.parents[i]);
    }
    dij_nodes[a.id].resolved=true;

    //if the current node is unreachable we keep going
    if (a.dist==INF) continue;

    // std::cout << "popped " << a.id << " with dist  " << a.dist << std::endl;
    // my_heap.print();


    for (const auto& kvp : edges[a.id]) {//continue here 
      int edge_node = kvp.first;
      if (!dij_nodes[edge_node].resolved) { //if this node has not yet been set
        int added_weight=kvp.second;
       

        if (added_weight + a.dist < dij_nodes[edge_node].dist) {
          dij_nodes[edge_node].dist = a.dist+added_weight;
          dij_nodes[edge_node].parents=std::vector<int>(1,a.id);
          my_heap.decrease_key(edge_node,dij_nodes[edge_node].dist);
        
        }
        else if (added_weight+ a.dist == dij_nodes[edge_node].dist) {
          //std::cout << "pushing here "<< std::endl;
          dij_nodes[edge_node].parents.push_back(a.id);
        }

      }
      
     

    }
  }



}



