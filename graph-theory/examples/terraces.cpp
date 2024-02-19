//example code for kattis problem "terraces"
//https://open.kattis.com/problems/terraces

#include<iostream>
#include "scc.h"
#include "visits_outside.h"

void read_data(int x, int y, std::unordered_map<int,std::unordered_map<int,int> >&);

int main() {

  int x,y;
  
  std::cin >> x >> y;
  std::unordered_map<int,std::unordered_map<int,int>> edges;
  read_data(x,y,edges);

  //way to print edges
  // for (int i = 0; i < x*y; i++) {
  //   std::cout << i << ": ";
  //   for (const auto& kvp : edges[i]) {
  //     std::cout << kvp.first << " ";
  //   }
  //   std::cout << std::endl;
  // }

  //run scc
  std::vector<std::unordered_set<int>> scc_order = scc(x*y,edges);

  // for (int i = 0; i < scc_order.size(); i++) {
  //   std::cout << i << ": ";
  //   for (int j : scc_order[i]) {
  //     std::cout << j << " ";
  //   }
  //   std::cout << std::endl;
  // }

  //check which scc's are sinks
  int num_terraces = 0;
  for (int i =0; i < scc_order.size(); i++) {
    if (!visits_outside(x*y,edges,scc_order[i])) {
      num_terraces += scc_order[i].size();
    }
  }

  std::cout << num_terraces << std::endl;
 
}



void read_data(int x, int y, std::unordered_map<int,std::unordered_map<int,int>>& edges) {
   std::vector<int> row1(x);
  std::vector<int> row2(x);
  std::vector<int>* temp;
  std::vector<int>* cur_row=&row2;
  std::vector<int>* old_row=&row1;

  //load in first value
  std::cin >> (*old_row)[0];
 
  for (int i = 1; i < x; i++) {
    std::cin >> (*old_row)[i];
    //compare left
    if ((*old_row)[i-1] >= (*old_row)[i]) {
      edges[i-1][i]=1;
    }
    if ((*old_row)[i-1] <= (*old_row)[i]) {
      edges[i][i-1]=1;
    }
  }  

  for (int j = 1; j < y; j++) {
  
    std::cin >> (*cur_row)[0];
  
    if ((*cur_row)[0] >= (*old_row)[0] ) {
    
      
      edges[j*x][(j-1)*x];
    }
    if ((*cur_row)[0] <= (*old_row)[0] ) {
     
      edges[(j-1)*x][j*x];
    } 

    for (int i = 1; i < x; i++) {
      std::cin >> (*cur_row)[i];
      if ((*cur_row)[i-1] >= (*cur_row)[i]) {
        edges[i-1+j*x][i+j*x];
      }
      if ((*cur_row)[i-1] <= (*cur_row)[i]) {
        edges[i+j*x][i-1+j*x];
      }
      if ((*cur_row)[i] >= (*old_row)[i]) {
        edges[i+j*x][i+(j-1)*x];
      }
      if ((*cur_row)[i] <= (*old_row)[i]) {
        edges[i+(j-1)*x][j*x+i];
      }
    }
    temp=old_row;
    old_row=cur_row; //move the pointers
    cur_row=temp;

  }
  

}