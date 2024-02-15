//code for book club kattis problem, found at https://open.kattis.com/problems/bookclub
#include "graph.h"
#include "hopcroft.h"
#include<iostream>

int main() {

  int M,N;
  std::cin >> N >> M;
  Graph g(N);
  int t1, t2;
  for (int i = 0; i < M; i++) {
    std::cin >> t1 >> t2;
    g.add_dedge(t1,t2);
  }
  if (g.hopcroft_karp() == N) std::cout << "YES" << std::endl;
  else std::cout << "NO" << std::endl;
  

}