//example code for shortestpath1: https://open.kattis.com/problems/shortestpath1
#include "graph.h"
#include "dijkstra.h"
#include<iostream>
#include<deque>
#include<unordered_set>
#include<unordered_map>

int main() {
  int n,m,q,s;
  int temp1,temp2,temp3;
  while (true) {
    std::cin >> n >> m >> q >> s;
    if (n==0 && m==0 && q==0 && s==0) break;
    Graph g(n);
    for (int i = 0; i < m; i++) {
      std::cin >> temp1 >> temp2 >> temp3;
      g.add_dedge(temp1,temp2,temp3);

    }
    g.dijkstra(s);
    for (int i = 0; i < q; i++) {
      std::cin >> temp1;
      
      if (g.nodes[temp1].dist != std::numeric_limits<long long>::max()) {
        std::cout << g.nodes[temp1].dist << std::endl;


      }
      else {
        std::cout << "IMPOSSIBLE" << std::endl;
      }

    }
  }

}