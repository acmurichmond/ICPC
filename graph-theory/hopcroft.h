// hopcroft-karp algorithm for perfect matching
// given a bipartite graph (WARNING: the code will not verify the graph is
// bipartite), return the number of matches in the best possible matching runs
// in O(|E| \sqrt(|V|)) time
#ifndef HOPCROFT_KARP
#define HOPCROFT_KARP

#include "graph.h"
#include <queue> //for queue

// hk bfs returns true if there is an augmenting path, false otherwise
bool Graph::hk_bfs() {
  std::queue<int> Q;

  for (int u = 0; u < n; u++) {
    if (pairU[u] == n) {
      hk_dist[u] = 0;
      Q.push(u);
    } else
      hk_dist[u] = std::numeric_limits<int>::max();
  }

  hk_dist[n] = std::numeric_limits<int>::max();

  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();

    if (hk_dist[u] < hk_dist[n]) {

      for (std::unordered_set<int>::iterator i = edges[u].begin();
           i != edges[u].end(); ++i) {
        int v = *i;
        if (hk_dist[pairV[v]] == std::numeric_limits<int>::max()) {
          hk_dist[pairV[v]] = hk_dist[u] + 1;
          Q.push(pairV[v]);
        }
      }
    }
  }

  return (hk_dist[n] != std::numeric_limits<int>::max());
}

bool Graph::hk_dfs(int u) {
  if (u != n) {
    std::unordered_set<int>::iterator i;
    for (i = edges[u].begin(); i != edges[u].end(); ++i) {
      // Adjacent to u
      int v = *i;

      // Follow the distances set by BFS
      if (hk_dist[pairV[v]] == hk_dist[u] + 1) {
        // If dfs for pair of v also returns
        // true
      
        if (hk_dfs(pairV[v])) // TODO use a non-recursive dfs here
        {
          pairV[v] = u;
          pairU[u] = v;
          return true;
        }
      }
    }

    // If there is no augmenting path beginning with u.
    hk_dist[u] = std::numeric_limits<int>::max();
    return false;
  }
  return true;
}

int Graph::hopcroft_karp() {

  // TODO can move these vectors outside if doing repeated hopcroft karp

  for (int i = 0; i < n + 1; i++) {
    pairU[i] = n;
    pairV[i] = n;
    hk_dist[i] = std::numeric_limits<int>::max();
  }

  int hk_result = 0;

  while (hk_bfs()) {
   
    for (int u = 0; u < n; u++) {
      if (pairU[u] == n && hk_dfs(u)) {
        hk_result += 1;
      }
    }

  
  }

  return hk_result;
}

#endif // HOPCROFT_KARP