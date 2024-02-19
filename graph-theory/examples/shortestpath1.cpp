//example code for shortestpath1: https://open.kattis.com/problems/shortestpath1
#include "dijkstra.h"
#include<iostream>
#include<deque>
#include<unordered_set>
#include<unordered_map>

int main() {
  int n,m,q,s;
  int temp1,temp2;
  long long temp3;
  while (true) {
    std::cin >> n >> m >> q >> s;
    if (n==0 && m==0 && q==0 && s==0) break;
    std::unordered_map<int, std::unordered_map<int, long long> > edges;
    for (int i = 0; i < m; i++) {
      std::cin >> temp1 >> temp2 >> temp3;
      //don't forget the duplicate edge guard!
      if (edges[temp1].find(temp2) == edges[temp1].end() || temp3 < edges[temp1][temp2]) {
        edges[temp1][temp2]=temp3;
      }

    }
    long long INF = std::numeric_limits<long long>::max();
    std::vector<long long> dists(n,INF);
    std::vector<std::vector<int>> parents(n);
    dijkstra(n,edges,s,dists,parents,INF);
    for (int i = 0; i < q; i++) {
      std::cin >> temp1;
      
      if (dists[temp1] != INF) {
        std::cout << dists[temp1] << std::endl;

      }
      else {
        std::cout << "Impossible" << std::endl;
      }

    }
  }

}