#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

struct Point {
    double x, y;
};

// find vertex w minimum key value, from set of vertices not yet included in MST
int minKey(vector<double>& key, vector<bool>& mstSet, int V) {
    double min = INT_MAX;
    int min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// print total length of edges in MST
void printMSTWeight(vector<int>& parent, vector<vector<double>>& graph, int V) {
    double w = 0;

    for (int i = 1; i < V; i++) {
        w += graph[i][parent[i]];
    }

    cout << w;
}

// A utility function to print constructed MST stored in parent[]
void printMST(vector<int>& parent, vector<vector<double>>& graph, int V){
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[i][parent[i]] << " \n";
}

// construct MST and print total length
void primMST(vector<vector<double>>& graph, int V) {
    vector<int> parent(V, -1);
    vector<double> key(V, 1000000000);
    vector<bool> mstSet(V, false);

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);                                    // pick min key vertex that hasnt been added yet
        mstSet[u] = true;                                                  // add to MST set

        for (int v = 0; v < V; v++) {                                      // update key value and parent index of adjacent vertices
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMSTWeight(parent, graph, V);                                      // calculate total length
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int V;
        cin >> V;                                                          // number of vertices

        vector<Point> islands(V);
        vector<vector<double>> graph(V, vector<double>(V, 0.0));           // graph represented in adjacency matrix

        for (int j = 0; j < V; ++j) {
            cin >> islands[j].x >> islands[j].y;                           // input points 
        }

        for (int i = 0; i < V; i++) {                                      // construct adjacency matrix
            for (int j = 0; j < V; j++) {
                double w = sqrt(pow((islands[i].x - islands[j].x), 2) + pow((islands[i].y - islands[j].y), 2));
                graph[i][j] = w;
            }
        }

        primMST(graph, V);                                              // create MST and print total length of mst
        cout << endl;
    }

    return 0;
}
