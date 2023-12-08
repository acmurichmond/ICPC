
#ifndef DFS
#define DFS
#include<deque> 

#include "graph.h"


//do dfs
//returns a set of all the nodes visited
//start is the start vertex
//if reverse is true, will use the reverse edges
//if postmark is true, will keep track of pre and post numbers
//if reset is false, do not reset the marks 
std::unordered_set<int> Graph::dfs(int start, bool reverse, bool postmark, bool reset_marks=true) {

  //reset marks
  if (reset_marks) {
    num_dead_ends=0;

    for (int i = 0; i < n; i++) {
      nodes[i].is_post_node=false;
      nodes[i].resolved_post_node=false;
      nodes[i].visited=false;
    }
    if (postmark) {
      order_num=0;
      for (int i = 0; i < n; i++) {
        nodes[i].pre=-1;
        nodes[i].post=-1;
      }
    }
  }

  std::deque<int> stack; //stores our dfs stack
  stack.push_back(start);
  std::unordered_set<int> visited_nodes; //stores all the nodes we visit during the dfs

  std::unordered_map<int,std::unordered_set<int>>* my_edges;
  //use reverse boolean to determine which edge set to use
  if (reverse) {
    my_edges=&rev_edges;
  }
  else {
    my_edges=&edges;
  }

  while (stack.size() > 0) {
    int s = stack.back(); //we pop from back of stack
    visited_nodes.insert(s);
    Node& cur_node = nodes[s];
    //if we have already seen this node
    if (cur_node.is_post_node && (! cur_node.resolved_post_node)) {
      if (postmark) {
        cur_node.post = order_num;
        order_num += 1;
      }
      stack.pop_back();
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
          if (!nodes[node].visited) stack.push_back(node);

        }

      }
    }
    else { //just pop
      stack.pop_back();
    }
  }

  return visited_nodes;

}

#endif