//Island hopping problem on kattis: 
//https://open.kattis.com/problems/islandhopping


#include "prims_minheap.h"
#include<iostream>
#include<vector>
#include<cmath>

int main() {
  int n;
  std::cin >> n;
  for (int test_case = 0; test_case < n; test_case++) {
   // std::cout << "hi" << std::endl;
    int m;
    std::cin >> m;  
    std::vector<std::pair<float,float>> islands(m);
    for (int i = 0; i < m; i++) {
      std::cin >> islands[i].first >> islands[i].second;
    }
    std::unordered_map<int, std::unordered_map<int, float> > edges;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        if (i < j) {
          float one_dist = islands[i].first-islands[j].first;
          float two_dist = islands[i].second-islands[j].second;
          float my_sqrt = sqrt(one_dist*one_dist+two_dist*two_dist);
          edges[i][j] = my_sqrt;
          edges[j][i] = my_sqrt;
        }
      }
    }

    // std::cout << "printing edges" << std::endl;
    // for (const auto& kvp1 : edges) {
    //   std::cout << kvp1.first << ": ";
    //   for (const auto& kvp2 : kvp1.second) {
    //     std::cout << kvp2.first << "(" << kvp2.second << "),";
    //   }
    //   std::cout << std::endl;
    // }

    float INF = std::numeric_limits<float>::max();
 
    auto mst_edges = prims(m,edges,INF);

    // std::cout << "printing mst edges " << std::endl;
    // for (std::pair<int,int> p : mst_edges) {
    //   std::cout << p.first << " " << p.second << std::endl;
    // }
  
    float final_weight = 0; 
    for (int i = 0; i < mst_edges.size(); i++) {
      final_weight += edges[mst_edges[i].first][mst_edges[i].second];
    }
    std::cout << final_weight << std::endl;

  }

}