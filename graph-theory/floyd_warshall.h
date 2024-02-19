#ifndef FLOYD_WARSHALL
#define FLOYD_WARSHALL

#include<limits>
#include<vector> 
#include<unordered_map>

//floyd-warshall computes the all-pairs shortest path for a graph
//INF, NEG_INF typically from numeric_limits (max & min) 
//fills into dist matrix instead of doing a copy return
//set reset_mat to true if you want to clear the matrix at the start of the run, otherwise set false
template<typename T>
void floyd_warshall(const int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, std::vector<std::vector<T>>& mat, T INF, T NEG_INF, bool reset_mat) {
  
  if (reset_mat) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        mat[i][j]=INF;
      }
    }

  }
  

  for (int i = 0; i < n; i++) { //0 distance from a node to itself
    mat[i][i]=0;
  }
  for (int i = 0; i < n; i++){
    for (const auto& kvp : edges[i]) {
      if (edges[i][kvp.first] < mat[i][kvp.first]) {
        mat[i][kvp.first] = kvp.second;
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


}
#endif //FLOYD_WARSHALL