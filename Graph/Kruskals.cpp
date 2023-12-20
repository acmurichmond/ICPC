#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class DSU {
    int* parent;
    int* rank;

public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    void unite(int x, int y)
    {
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
};

class Graph {
    vector<vector<double>> edgelist;
    int V;

public:
    Graph(int V) { this->V = V; }

    void addEdge(double x, double y, double w)
    {
        edgelist.push_back({ w, x, y });
    }

    void kruskals_mst()
    {
        sort(edgelist.begin(), edgelist.end());

        DSU s(V);
        double ans = 0;
        for (auto edge : edgelist) {
            double w = edge[0];
            double x = edge[1];
            double y = edge[2];

            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                ans += w;
            }
        }
        cout << fixed << setprecision(9) << ans << endl;
    }
};

struct Point {
    double x, y;
};

int main(){
    int m = 5;                                                                                    // number of points in graph
    
    vector<Point> islands(m);
    
    for (int j = 0; j < m; ++j) {                                                                //input points     
        cin >> islands[j].x >> islands[j].y;
    }
    
    Graph g(m);                                                                                 //complete graph with all inputted points
    
    double w = 0;
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            w = pow((islands[i].x - islands[j].x), 2) + pow((islands[i].y - islands[j].y), 2);
            w = sqrt(w);                                                                         // calculate distance between points and add edge to graph
            g.addEdge((double)i, (double)j, w);
        }
    }
    g.kruskals_mst();                                                                           //create mst and output the total length of the graph
    return 0;
}
