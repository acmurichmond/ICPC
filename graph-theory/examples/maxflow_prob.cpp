//https://open.kattis.com/problems/maxflow
#include<iostream>
#include "maxflow.h"
#include<limits> //include this! otherwise compile error :)

int main() { //continue here

  int n, m, s, t;
  std::cin >> n >> m >> s >> t;
  int t1, t2, t3;
  std::unordered_map<int, std::unordered_map<int, int> > edges;
  for (int i = 0; i < m; i++) {
    std::cin >> t1 >> t2 >> t3;
    //because this is flow, we add duplicate edge weights (because they are capacities)
    //undirected**
    if (edges[t1].find(t2) != edges[t1].end()) {
      edges[t1][t2] += t3;
     // edges[t2][t1] += t3;
    }
    else {
      edges[t1][t2] = t3;
   //   edges[t2][t1] = t3; 
    }
  }

  // std::cout << "printing edges " << std::endl;
  // for (const auto& kvp1 : edges) {
  //   std::cout << kvp1.first << ": ";
  //   for (const auto& kvp2 : kvp1.second) {
  //     std::cout << kvp2.first << "(" << kvp2.second << ")" << " ";

  //   }
  //   std::cout << std::endl;
  // }

  int INF = std::numeric_limits<int>::max();

 //std::cout << "Hi!" << std::endl;
  //we declare R but do not input values into it
  std::unordered_map<int, std::unordered_map<int,int> > R;


  int flow = maxflow(n,edges,R,s,t,INF);

 // std::cout << "flow: " <<flow << std::endl;

  int num_edges_used=0; //initialize to 0**! (otherwise some rand value potentially)
  for (const auto& kvp1 : R) {
    for (const auto& kvp2 : kvp1.second) {
      if (kvp2.second < edges[kvp1.first][kvp2.first] && kvp2.second >= 0) { //then capacity positive, this edge used in output
        num_edges_used += 1;

      }
    }
  }

 // std::cout << "num edges used: " << num_edges_used << std::endl;
 std::cout << n << " " << flow << " " << num_edges_used << std::endl;

  for (const auto& kvp1 : R) {
    for (const auto& kvp2 : kvp1.second) {
      if (kvp2.second < edges[kvp1.first][kvp2.first] && kvp2.second >= 0) { //then capacity positive, this edge used in output
        std::cout << kvp1.first << " " << kvp2.first << " " << edges[kvp1.first][kvp2.first] - kvp2.second << std::endl;

      }
    }
  }

  


}