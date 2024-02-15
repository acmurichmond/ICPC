#ifndef RANDOM_GRAPH
#define RANDOM_GRAPH

#include <cstdlib> 
#include "graph.h"
#include <time.h>

Graph Graph::random_graph(int n, int edge_chance, int min_weight, int max_weight) {
  std::srand(time(0));
  Graph g(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && std::rand()%100 < edge_chance) {
        int edge_weight = rand() % (max_weight-min_weight) + min_weight;
        g.add_dedge(i,j,edge_weight);
      }
    }
  }
  return g;

  
}




#endif //RANDOM_GRAPH