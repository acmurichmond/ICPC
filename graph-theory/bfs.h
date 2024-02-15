//bfs function

#ifndef BFS
#define BFS
#include<deque> 

#include "graph.h"


  //do bfs
  //returns a set of all the nodes visited
  //start is the start vertex
  //if reverse is true, will use the reverse edges
  //if postmark is true, will keep track of pre and post numbers
  std::unordered_set<int> Graph::bfs(std::vector<int> starts, bool reverse=false, bool postmark=false) {
    std::deque<int> stack;

    //reset marks
    num_dead_ends=0;

    for (int i = 0; i < n; i++) {
      nodes[i].is_post_node=false;
      nodes[i].resolved_post_node=false;
      nodes[i].visited=false;
      nodes[i].depth=std::numeric_limits<int>::max();
    }
    if (postmark) {
      order_num=0;
      for (int i = 0; i < n; i++) {
        nodes[i].pre=-1;
        nodes[i].post=-1;
      }
    }
    for (int i : starts) {
      stack.push_back(i);
      nodes[i].depth=0;
    }
    std::unordered_set<int> visited_nodes;

    std::unordered_map<int,std::unordered_set<int>>* my_edges;
    //use reverse boolean to determine which edge set to use
    if (reverse) {
      my_edges=&rev_edges;
    }
    else {
      my_edges=&edges;
    }
  
    while (stack.size() > 0) {
      int s = stack.front(); //note that bfs takes from front of stack, not back like dfs
      visited_nodes.insert(s);
      Node& cur_node = nodes[s];
      //if we have already seen this node
      if (cur_node.is_post_node && (! cur_node.resolved_post_node)) {
        if (postmark) {
          cur_node.post = order_num;
          order_num += 1;
        }
        stack.pop_front();
        cur_node.resolved_post_node=true;

      }
      else if (!cur_node.is_post_node) {
        cur_node.is_post_node=true;
        //if we haven't yet visited this node
        if (! cur_node.visited) {
          //if we are postmarking, mark the pre number
          if (postmark) {
            cur_node.pre=order_num;
            order_num+=1;
          }
          cur_node.visited=true;

          //if this is a dead end
          if ((*my_edges)[s].empty()) {
            num_dead_ends += 1;
          }
          //for each neighbor
          for (int node : (*my_edges)[s]) {
            //if we haven't visited it yet
            if (!nodes[node].visited) {
             
              stack.push_back(node);
              nodes[node].depth = std::min(cur_node.depth + 1,nodes[node].depth);
            
            }
          }

        }
      }
      else { //just pop
        stack.pop_front();
      }
    }

    return visited_nodes;

  }

#endif