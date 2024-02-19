//using the floyd warshall algorithm for an all pairs shortest path problem
//for kattis problem:
//https://open.kattis.com/problems/allpairspath
#include "floyd_warshall.h"
#include<iostream>
#include<limits>
#include<unordered_map>

int main() {
  int n,m,q,t1,t2,t3;
  while (true) {
    std::cin >> n >> m >> q;
    if (n==0 && m==0 && q==0) break;
    std::unordered_map<int,std::unordered_map<int,long long> > edges;
    for (int i = 0; i < m; i++) {
      std::cin >> t1 >> t2 >> t3;
      //protect against adding duplicate edges with different costs (not it)
      if (edges[t1].find(t2) == edges[t1].end() || (t3 < edges[t1][t2])) {
        edges[t1][t2]=t3;
        
      }
     

    }

    long long INF = std::numeric_limits<long long>::max();
    long long NEG_INF = std::numeric_limits<long long>::min();
    std::vector<std::vector<long long>> mat(n, std::vector<long long>(n,INF));

    floyd_warshall(n,edges,mat,INF,NEG_INF,false);

    for (int i = 0; i < q; i++) {
      std::cin >> t1 >> t2;
      if (mat[t1][t2]==INF) {
        std::cout << "Impossible" << std::endl;
      }
      else if (mat[t1][t2]==NEG_INF) {
        std::cout << "-Infinity" << std::endl;
      }
      else {
        std::cout << mat[t1][t2] << std::endl;
      }
    }
    //std::cout << std::endl;

  }

}