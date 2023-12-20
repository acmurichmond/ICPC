//bellman ford algorithm
#include "graph.h"
#include "dfs.h"

//returns true if negative weight cycle
//TODO implement reverse feature (not currently implemented)
bool Graph::bellman_ford(int s, bool reverse=false, bool reset=true) {
  typedef long long ll;
  if (reset) {
    for (int i = 0; i < n; i++) {
      nodes[i].dist=INF;
    }
   
  }
  if (reverse==true) {
    std::cout << "Feature not set, aborting" <<std::endl;
    exit(7);
  }
  nodes[s].dist=0;

  bool update_made=true;

  for (int i  = 0; i < n-1; i++) {
    update_made=false;
    //for each edge
    for (int j = 0; j < n; j++) {
      for (int k : edges[j]) {
        if (nodes[j].dist != INF && nodes[j].dist + weights[j][k] < nodes[k].dist) {
          nodes[k].dist=nodes[j].dist+weights[j][k];
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
    for (int k : edges[j]) { 
      if ((nodes[j].dist != INF && nodes[j].dist + weights[j][k] < nodes[k].dist) || nodes[j].dist==NEG_INF) {
        nodes[k].dist = NEG_INF;
        any_neg=true;
      }
    }
  }
  if (any_neg) {
    for (int i = 0; i < n; i++) {
      nodes[i].is_post_node=false;
      nodes[i].resolved_post_node=false;
      nodes[i].visited=false;

    }

  //all nodes reachable from a NEG_INF node are NEG_INF
  for (int i = 0; i < n; i++) {
    if (nodes[i].dist == NEG_INF && !nodes[i].visited) {
      auto visited_nodes = dfs(i,false,false,false); //dfs without resetting marks
      for (int j : visited_nodes) {
        nodes[j].dist=NEG_INF;
      }
    }
  }

  }


 
  return any_neg;

  
}
