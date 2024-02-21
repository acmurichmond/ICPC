#ifndef KRUSKAL
#define KRUSKAL

#include<algorithm>

//adapted from Lauren's DSU code in Kruskals.cpp
class DSU {
    int* parent;
    int* rank;

public:
    DSU(int n){
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    int find(int i){
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    void unite(int x, int y){
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            } else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            } else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
    ~DSU() {
      delete[] parent;
      delete[] rank;
    }
};

bool pair_compare(std::pair<float,std::pair<int,int>> a,std::pair<float,std::pair<int,int>> b ) {
  return a.first < b.first;
}
//find the MST of a graph, return as vector of edge pairs USING kruskals
//WARNING: if time limit exceeded, just don't make a graph and insert the edges directly to a weight edge pairs framework
template<typename T>
std::vector<std::pair<int,int>> kruskals(int n, std::unordered_map<int, std::unordered_map<int, T> >& edges) {

  //copy over to weight edge pairs array
  std::vector<std::pair<float,std::pair<int,int>>> weight_edge_pairs;
  for (int i = 0; i < n; i++) {
    for (const auto& kvp : edges[i]) { //for each terminal vertex, weight of edge pair
      weight_edge_pairs.push_back(std::make_pair(kvp.second,std::make_pair(i,kvp.first)));

    }
  }
 
  std::sort(weight_edge_pairs.begin(),weight_edge_pairs.end(),pair_compare);
  std::vector<std::pair<int,int>> mst_edges;
  DSU s(n);
  for (int i = 0; i < weight_edge_pairs.size(); i++) {
    std::pair<int,int> edge = weight_edge_pairs[i].second;
    if (s.find(edge.first) != s.find(edge.second)) {
      s.unite(edge.first,edge.second);
      mst_edges.push_back(weight_edge_pairs[i].second);
      if (mst_edges.size()==n-1) {
        break;
      }
    }

  }

 

 return mst_edges;

}





#endif //KRUSKAL