//using the floyd warshall algorithm for an all pairs shortest path problem

#include "graph.h"
#include "floyd_warshall.h"
#include<iostream>
#include<limits>
#include<unordered_set>

int main() {
  int n,m,q,t1,t2,t3;
  while (true) {
    std::cin >> n >> m >> q;
    if (n==0 && m==0 && q==0) break;
    Graph g(n);
    for (int i = 0; i < m; i++) {
      std::cin >> t1 >> t2 >> t3;
      //protect against adding duplicate edges with different costs (not it)
      if (g.edges[t1].find(t2) != g.edges[t1].end()) {
        if (t3 < g.weights[t1][t2]) {
          g.weights[t1][t2]=t3;
        }
      }
      else {
        g.add_dedge(t1,t2,t3);
      }

    }
    auto mat = g.floyd_warshall();
    for (int i = 0; i < q; i++) {
      std::cin >> t1 >> t2;
      if (mat[t1][t2]==g.INF) {
        std::cout << "Impossible" << std::endl;
      }
      else if (mat[t1][t2]==g.NEG_INF) {
        std::cout << "-Infinity" << std::endl;
      }
      else {
        std::cout << mat[t1][t2] << std::endl;
      }
    }
    //std::cout << std::endl;

  }

}