#include "graph.h"
#include<unordered_set> 
#include<unordered_map>
#include<queue>
#include<deque>
#include <unistd.h> //TODO what for?

#include "min_heap.h"

void Graph::dijkstra(int start, bool reverse=false, bool reset=true) {


  typedef long long ll;

  //std::cout << "starting dijkstra" << std::endl;
  if (reset) {
    for (int i = 0; i < n; i++) {
      nodes[i].dist=std::numeric_limits<int>::max();
      nodes[i].dij_parents.clear();
    }
  }

  std::unordered_map<int,std::unordered_set<int>>* my_edges;
  //use reverse boolean to determine which edge set to use
  if (reverse) {
    my_edges=&rev_edges;
  }
  else {
    my_edges=&edges;
  }

  struct DijNode {
    int id;
    ll dist;
    bool valid;
    std::vector<int> parents;
    bool resolved;
    DijNode(int id,ll dist) : id(id),dist(dist),valid(true),resolved(false) {
      parents=std::vector<int>();
    }
    DijNode() : id(-1),dist(std::numeric_limits<ll>::max()),valid(false),resolved(false) {
      parents=std::vector<int>();
    }
  };



  MinHeap my_heap;
  std::unordered_map<int,DijNode> dij_nodes;
  for (int i = 0; i < n; i++) {
    dij_nodes[i] = DijNode(i,INF);
  }

  for (int i = 0; i < n; i++) {
    my_heap.insert(i,dij_nodes[i].dist);
  }

  dij_nodes[start].dist=0;
  my_heap.decrease_key(start,0);

 //my_heap.print();

  
  while (!my_heap.empty()) {
 
    DijNode& a = dij_nodes[my_heap.delete_min()];


    nodes[a.id].dist=a.dist; //write in the answer
    for (int i = 0; i < a.parents.size(); i++) {
      nodes[a.id].dij_parents.push_back(a.parents[i]);
    }
    dij_nodes[a.id].resolved=true;

    //if the current node is unreachable we keep going
    if (a.dist==INF) continue;

    // std::cout << "popped " << a.id << " with dist  " << a.dist << std::endl;
    // my_heap.print();


    for (int edge_node : (*my_edges)[a.id]) {
      if (!dij_nodes[edge_node].resolved) { //if this node has not yet been set
        int added_weight;
        if (reverse) added_weight=weights[edge_node][a.id];
        else added_weight=weights[a.id][edge_node];

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



