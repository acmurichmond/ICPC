// hopcroft-karp algorithm for perfect matching
// given a bipartite graph (WARNING: the code will not verify the graph is
// bipartite), return the number of matches in the best possible matching runs
// in O(|E| \sqrt(|V|)) time
#ifndef HOPCROFT_KARP
#define HOPCROFT_KARP

#include <queue> //for queue
#include<unordered_map>

// hk bfs returns true if there is an augmenting path, false otherwise
template<typename T>
bool hk_bfs(int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, std::vector<int>& pairU, std::vector<int>& pairV, std::vector<T>& hk_dist, T INF) {
  std::queue<int> Q;

  for (int u = 0; u < n; u++) {
    if (pairU[u] == n) {
      hk_dist[u] = 0;
      Q.push(u);
    } else
      hk_dist[u] = INF;
  }

  hk_dist[n] = INF;

  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();

    if (hk_dist[u] < hk_dist[n]) {

      for (const auto& kvp : edges[u]) {
        int v = kvp.first;
        if (hk_dist[pairV[v]] == INF) {
          hk_dist[pairV[v]] = hk_dist[u] + 1;
          Q.push(pairV[v]);
        }
      }
    }
  }

  return (hk_dist[n] != INF);
}
template<typename T>
bool hk_dfs(int u,int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, std::vector<int>& pairU, std::vector<int>& pairV, std::vector<T>& hk_dist, T INF) {
  if (u != n) {
    for (const auto& kvp : edges[u]) {
 
      int v = kvp.first;

      // Follow the distances set by BFS
      if (hk_dist[pairV[v]] == hk_dist[u] + 1) {
        // If dfs for pair of v also returns
        // true
      
        if (hk_dfs(pairV[v],n,edges,pairU,pairV,hk_dist,INF)) // TODO use a non-recursive dfs here
        {
          pairV[v] = u;
          pairU[u] = v;
          return true;
        }
      }
    }

    // If there is no augmenting path beginning with u.
    hk_dist[u] = INF;
    return false;
  }
  return true;
}

//run hopcroft karp
template<typename T>
int hopcroft_karp(int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, T INF) {

  std::vector<int> pairU(n+1,n);
  std::vector<int> pairV(n+1,n);
  std::vector<T> hk_dist(n+1,INF);

  int hk_result = 0;

  while (hk_bfs(n,edges,pairU,pairV,hk_dist,INF)) {
   
    for (int u = 0; u < n; u++) {
      if (pairU[u] == n && hk_dfs(u,n,edges,pairU,pairV,hk_dist,INF)) {
        hk_result += 1;
      }
    }

  
  }

  return hk_result;
}

#endif // HOPCROFT_KARP