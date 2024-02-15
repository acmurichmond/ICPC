#include<iostream>
#include "graph.h"
#include "bellman_ford.h"
#include "dfs.h"

int main() {


  int n,m,q,s,t1,t2,t3;
  while (true) {
    std::cin >> n >> m >> q >> s;
    if (n==0 && m==0 && q==0 && s==0) {
      break;
    }
    Graph g(n);
    for (int i = 0; i < m; i++) {
      std::cin >> t1 >> t2 >> t3;
      //handle case of double edges TODO mark in README
      if (g.edges[t1].find(t2) != g.edges[t1].end()) {
        if (t3 < g.weights[t1][t2]) {
          g.weights[t1][t2]=t3;
        }
      }
      else {
        g.add_dedge(t1,t2,t3);


      }

    }
    bool is_inf = g.bellman_ford(s);
    for (int i = 0; i < q; i++) {
      std::cin >> t1;
      if (g.nodes[t1].dist == g.INF) {
        std::cout << "Impossible" << std::endl;
      }
      else if (g.nodes[t1].dist == g.NEG_INF) {
        std::cout << "-Infinity" << std::endl;
      }
      else {
        std::cout << g.nodes[t1].dist << std::endl;
      }
    }


  }

}