//general graph class
#ifndef GRAPH
#define GRAPH

#include<iostream>
#include<unordered_map>
#include<vector>
#include<unordered_set>
#include<limits> //for numeric_limits::max
#include<deque>

struct Node {
  int id; //id of node (integer 0->n-1)
  int pre; //pre number in dfs
  int post; //post number in dfs
  bool visited; //whether node has been visited
  bool is_post_node; //whether node is waiting in stack as post node
  bool resolved_post_node; //whether node has already been processed as post node
  bool vo_mark; //special mark for vo = visit outside function
  int depth; //depth from start (in BFS)
  long long dist; //distance from start node (dijkstra)
  std::vector<int> dij_parents;

  Node(int id) : id(id),pre(-1),post(-1),visited(false),is_post_node(false),resolved_post_node(false),vo_mark(false),depth(std::numeric_limits<int>::max()),dist(std::numeric_limits<long long>::max()) {}

};

struct Graph {

  const long long INF = std::numeric_limits<long long>::max();
  const long long NEG_INF = std::numeric_limits<long long>::min();


  int n; //number of vertices
  int order_num; //used internally for pre and post number calculation
  int num_dead_ends; //keep track of the number of dead ends in a graph

  //nodes of graph
  std::vector<Node> nodes;

  //hopcroft karp perfect matching specific
  std::vector<int> pairU;
  std::vector<int> pairV;
  std::vector<int> hk_dist;

  //edges of graph. Stored as a hashmap mapping a node u to a set of nodes v_1, v_2, ... v_n that are adjacent to u
  std::unordered_map<int,std::unordered_set<int>> edges;
  //the reverse edges in the graph
  std::unordered_map<int,std::unordered_set<int>> rev_edges;
  //stores the weight of each edge, only for the edges in the graph
  std::unordered_map<int,std::unordered_map<int,int>> weights; 

  //graph constructor just takes the number of vertices in the graph
  Graph(int n) : n(n) {

    nodes=std::vector<Node>();
    nodes.reserve(n);
  
    for (int i = 0; i < n; i++) {
      edges[i] = std::unordered_set<int>();
      rev_edges[i] = std::unordered_set<int>();
      weights[i]=std::unordered_map<int,int>();
      nodes.push_back(Node(i));
    }
    order_num=0;
    num_dead_ends=0;

    pairU=std::vector<int>(n+1);
    pairV=std::vector<int>(n+1);
    hk_dist=std::vector<int>(n+1);
  }

  //add an unweighted directed edge (directed edge=dedge) to the graph
  //u is start vertex, z is end vertex

  void add_dedge(int u, int z) {
    edges[u].insert(z);
    rev_edges[z].insert(u);
    weights[u][z]=1;
  }
  //add a weighted edge to the graph
  //u is start vertex, z is end vertex, w is weight
  //it is common for problems to offer duplicate edges, when duplicate_edge_guard is set to true we automatically choose the smaller of the 2 edges. Without this flag, we pick the most recently inserted weight.
  void add_dedge(int u, int z, int w,bool duplicate_edge_guard=true) {

    if (!duplicate_edge_guard || edges[u].find(z) == edges[u].end() || weights[u][z] > w) {
      weights[u][z]=w;
    }
    edges[u].insert(z);
    rev_edges[z].insert(u);
  


  }
  //uedge = unweighted edge
  void add_uedge(int u, int z) {
    add_dedge(u,z);
    add_dedge(z,u);
  }
  void add_uedge(int u, int z, int w) {
    add_dedge(u,z,w);
    add_dedge(z,u,w);
  }

  //print the graph
  void print_graph() {
    std::cout << "Graph with " << n << " nodes." << std::endl;
    std::cout << "Edges: " << std::endl;
    for (int i = 0; i < n; i++) {
      std::cout << i << ": ";
      for (int j : edges[i]) {
        std::cout << j << "(" << weights[i][j] << "), ";
      }
      std::cout << std::endl;
    }
    std::cout << "Nodes with pre/post/dist: " << std::endl;
    for (int i = 0; i < n; i++) {
      std::cout << "id: " << i << " pre: " << nodes[i].pre << " post: " << nodes[i].post << " depth: " << nodes[i].depth << " dij dist: " << nodes[i].dist << std::endl;
    }
  }


  std::unordered_set<int> dfs(int start, bool reverse, bool postmark,bool reset_marks);
  std::unordered_set<int> bfs(std::vector<int> starts, bool reverse, bool postmark);
  std::vector<std::unordered_set<int>> scc();
  bool visits_outside(std::unordered_set<int> node_set, bool reverse, bool set_mark_false);
  int hopcroft_karp();
  bool hk_bfs();
  bool hk_dfs(int u);
  void dijkstra(int s, bool reverse, bool reset);
  std::pair<int,std::deque<int>> dijkstra(int s, int t, bool reverse, bool reset);
  std::vector<std::vector<long long>> floyd_warshall();
  Graph random_graph(int n, int edge_chance, int min_weight, int max_weight);
  bool bellman_ford(int s, bool reverse, bool reset);

};

#endif //GRAPH