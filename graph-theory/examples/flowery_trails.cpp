//example code for flowery trails: https://open.kattis.com/problems/flowerytrails
//g++ -o ac.out -std=c++17 examples/flowery_trails.cpp -I.
#include "dijkstra.h"
#include<iostream>
#include<deque>
#include<unordered_set>
#include<unordered_map>

int main() {
  int P,T,temp1,temp2,temp3;
  std::cin >> P >> T;
  std::unordered_map<int,std::unordered_map<int,int>> num_edges;
  for (int i = 0; i < P; i++) {
    num_edges[i]=std::unordered_map<int,int>();
  }
  
  std::unordered_map<int,std::unordered_map<int ,int> > edges;
  for (int i = 0; i < T; i++) {
    std::cin >> temp1 >> temp2 >> temp3;
    if (temp1 == temp2) { //we don't care about self cycles
      continue;
    }
    //if we've seen an edge between these two verts b4
    //find != .end alternate to contains
    if (num_edges[temp1].find(temp2) != num_edges[temp1].end()) {
      if (temp3 < edges[temp1][temp2]) {
        edges[temp1][temp2]=temp3;
        edges[temp2][temp1]=temp3;
        num_edges[temp1][temp2]=1;
        num_edges[temp2][temp1]=1;
      }
      else if (temp3 == edges[temp1][temp2]) {
        num_edges[temp1][temp2] += 1;
        num_edges[temp2][temp1] += 1;
      }

    }
    //if this is the first time we see this edge, add edge normally
    else {
      num_edges[temp1][temp2] = 1;
      num_edges[temp2][temp1] = 1;
      edges[temp1][temp2]=temp3;
      edges[temp2][temp1]=temp3;
    }
   
    
  }

  int INF = std::numeric_limits<int>::max();
  std::vector<int> dists(P,INF);
  std::vector<std::vector<int>> parents(P);

  dijkstra(P,edges,0,dists,parents,INF);

  long path_length=0;

  std::deque<int> stack;
  
  stack.push_back(P-1);
  //iterate through all the shortest paths, recording the path length (the length of the paths on which we are planting flowers)
  while (!stack.empty()) {
  
    int s = stack.front();
    stack.pop_front();
    //std::cout << "looking at s " << s << std::endl;
    for (int i : parents[s]) {
    //  std::cout << "s parent is " << i << std::endl;
    //  std::cout << "weight of  " << s << " to " << i << " is " << g.weights[s][i] << ", times " << num_edges[s][i] << std::endl;
      path_length += edges[s][i] * num_edges[s][i];
      //avoid double-flowering a path FIXME time blowup with parents? 
      num_edges[s][i]=0;
      num_edges[i][s]=0;
      stack.push_back(i);
    }

  }
  std::cout << path_length*2 << std::endl;



}