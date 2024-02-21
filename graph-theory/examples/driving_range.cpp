
#include "kruskals.h"
#include<iostream>
#include<algorithm>

int main() {

  std::ios_base::sync_with_stdio(false); //fast IO
  std::cin.tie(NULL); //fast IO

  int n,m;
  std::cin >> n >> m;


  if (n<=1) {
    std::cout << 0 << std::endl;
  }
 
  std::unordered_map<int, std::unordered_map<int, int> > edges;

  int t1,t2,t3;

  for (int i = 0 ; i < m; i++) {
    std::cin >> t1 >> t2 >> t3;
    //note the dup edge guard here
    if (edges[t1].find(t2) == edges[t1].end() || t3 < edges[t1][t2]) {
      edges[t1][t2] = t3;
      edges[t2][t1] = t3;
    }

  }

  auto mst_edges = kruskals(n,edges);
   
  if (mst_edges.size() < n-1) {
    std::cout << "IMPOSSIBLE" << std::endl;
  }
  else {
    int max_length = 0;
    for (int i =0 ; i < mst_edges.size(); i++) {
      max_length = std::max(edges[mst_edges[i].first][mst_edges[i].second],max_length);

    }
    std::cout << max_length << std::endl;
  }
   
    


}