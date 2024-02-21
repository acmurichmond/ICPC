//code for book club kattis problem, found at https://open.kattis.com/problems/bookclub
#include "hopcroft.h"
#include<iostream>
#include<unordered_map>
#include<limits>

int main() {

  int M,N;
  std::cin >> N >> M;
  std::unordered_map<int, std::unordered_map<int, int> > edges;
  int t1, t2;
  for (int i = 0; i < M; i++) {
    std::cin >> t1 >> t2;
    edges[t1][t2]=1;
  }

  int INF = std::numeric_limits<int>::max();

  if (hopcroft_karp(N,edges,INF) == N) std::cout << "YES" << std::endl;
  else std::cout << "NO" << std::endl;
  

}