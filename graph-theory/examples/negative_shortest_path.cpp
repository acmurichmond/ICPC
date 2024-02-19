#include<iostream>
#include "bellman_ford.h"
#include<unordered_map>

//solves kattis problem
//https://open.kattis.com/problems/shortestpath3
int main() {

  int n,m,q,s,t1,t2,t3;
  while (true) {
    std::cin >> n >> m >> q >> s;
    if (n==0 && m==0 && q==0 && s==0) {
      break;
    }
    std::unordered_map<int,std::unordered_map<int,long long> > edges;
    for (int i = 0; i < m; i++) {
      std::cin >> t1 >> t2 >> t3;
      //t3 < edges[t1][t2] check handles case of duplicate edges (just use the smaller one always) 
      if (edges[t1].find(t2) == edges[t1].end() || t3 < edges[t1][t2]) {
        edges[t1][t2]=t3;
      }
      

    }

    //print edges
    // for (int i = 0; i < n; i++) {
    //   std::cout << i << ": ";
    //   for (const auto& kvp : edges[i]) {
    //     std::cout << kvp.first << "(" << kvp.second << ") ";
    //   }
    //   std::cout << std::endl;
    // }


    long long NEG_INF = std::numeric_limits<long long>::min();
    long long INF = std::numeric_limits<long long>::max();
    std::vector<long long> dist = bellman_ford(n,edges,s,INF,NEG_INF);
    for (int i = 0; i < q; i++) {
      std::cin >> t1;
      if (dist[t1]== INF) {
        std::cout << "Impossible" << std::endl;
      }
      else if (dist[t1] == NEG_INF) {
        std::cout << "-Infinity" << std::endl;
      }
      else {
        std::cout << dist[t1] << std::endl;
      }
    }


  }

}