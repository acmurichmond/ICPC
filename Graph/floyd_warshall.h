#ifndef FLOYD_WARSHALL
#define FLOYD_WARSHALL

#include "graph.h"
#include<limits>
//floyd-warshall computes the all-pairs shortest path for a graph
std::vector<std::vector<long long>> Graph::floyd_warshall() {

  std::vector<std::vector<long long>> mat(n,std::vector<long long>(n,INF));


  for (int i = 0; i < n; i++) { //0 distance from a node to itself
    mat[i][i]=0;
  }
  for (int i = 0; i < n; i++){
    for (int j : edges[i]) {
      if (weights[i][j] < mat[i][j]) {
        mat[i][j] = weights[i][j];
      }
    }
   
  }

   for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (mat[i][j] > mat[i][k] + mat[k][j] && mat[i][k] < INF && mat[k][j] < INF) {
                        mat[i][j] = mat[i][k] + mat[k][j];
                    }
                }
            }
        }

        //neg cycles
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; mat[i][j] != NEG_INF && k < n; k++) {
                    if (mat[k][k] < 0 && mat[i][k] != INF && mat[k][j] != INF) {
                        mat[i][j] = NEG_INF;
                    }
                }	
            }
        }
  return mat;


}
#endif //FLOYD_WARSHALL