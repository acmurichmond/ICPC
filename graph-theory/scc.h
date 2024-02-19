#ifndef SCCN
#define SCCN

#include<algorithm> //for sort
#include<deque>
#include<unordered_set> 
#include<unordered_map> 
#include<iostream>


//postmarking version of dfs, helper for scc
template<typename T>
int scc_dfs(const int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, int start, std::vector<bool>& visited, std::vector<int>& pre, std::vector<int>& post, std::vector<bool>& is_post_node, std::vector<bool>& resolved_post_node, int order_num) {

  std::deque<int> stack; //stores our dfs stack
  stack.push_back(start);

  while (stack.size() > 0) {
    int s = stack.back(); //we pop from back of stack
 
    //if we have already seen this node
    if (is_post_node[s] && (! resolved_post_node[s])) {
     
      post[s] = order_num;
      order_num += 1;
      
      stack.pop_back();
      resolved_post_node[s]=true;

    }
    else if (!is_post_node[s]) {
      is_post_node[s]=true;
      //if we haven't yet visited this node
      if (!visited[s]) {
       
        pre[s]=order_num;
        order_num+=1;
        visited[s]=true;

        //for each neighbor
        for (const auto& kvp : edges[s]) {
          //if we haven't visited it yet
          if (!visited[kvp.first]) stack.push_back(kvp.first);

        }

      }
    }
    else { //just pop
      stack.pop_back();
    }
  }

  return order_num;

}


//version of dfs that takes in visited array
template<typename T> 
std::unordered_set<int> scc_dfs2(int n, std::unordered_map<int,std::unordered_map<int,T> >& edges, int start,std::vector<bool>& visited) {
  
  std::deque<int> stack; //stores our dfs stack
  stack.push_back(start);
  std::unordered_set<int> visited_nodes; //stores all the nodes we visit during the dfs

  while (stack.size() > 0) {
    int s = stack.back(); //we pop from back of stack
    stack.pop_back();
    visited_nodes.insert(s);
   
    //if we haven't yet visited this node
    if (! visited[s]) {
      visited[s]=true;
      //for each neighbor
      for (const auto& kvp : edges[s]) { //kvp = key value pair
        //if we haven't visited it yet
        if (!visited[kvp.first]) stack.push_back(kvp.first);

      }
    }
  }
  return visited_nodes;
}


//scc returns a list of connected components, in the form of sets. 
//By construction, the sets are ordered from sources to sinks
template<typename T>
std::vector<std::unordered_set<int>> scc(int n,std::unordered_map<int,std::unordered_map<int,T> >& edges) {
  
  int order_num=0;
  std::vector<bool> is_post_node(n,false);
  std::vector<bool> resolved_post_node(n,false);
  std::vector<bool> visited(n,false);
  std::vector<int> pre(n,-1);
  std::vector<int> post(n,-1);
  int start_node=0; 
  while (order_num < 2*n) {
    if (start_node >= n) {
      std::cout << "Error start_node exceeded bound " << std::endl;
      exit(7);
    }
    order_num=scc_dfs(n,edges,start_node,visited,pre,post,is_post_node,resolved_post_node,order_num);
    start_node+=1;
  }
  std::vector<int> sorted_nodes(n);
  for (int i = 0; i < n; i++) {
    sorted_nodes[i]=i;
  }
  std::sort(sorted_nodes.begin(),sorted_nodes.end(), [&] (int a, int b) {return post[a] > post[b];});

  std::vector<std::unordered_set<int>> scc_order;

  for (int i = 0; i < n; i++) {
    visited[i]=false;
  }

  //scc needs rev graph
  std::unordered_map<int, std::unordered_map<int,int> > rev_edges;
  for (int i = 0; i < n; i++) {
    for (const auto& kvp : edges[i]) {
      rev_edges[kvp.first][i]=kvp.second;
    }
  }

 
  for (int i = 0; i < n; i++) {
    int node = sorted_nodes[i];
    if (!visited[node]) {
      scc_order.push_back(scc_dfs2(n,rev_edges,node,visited));
    }
  }

  return scc_order;

}



#endif