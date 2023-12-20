//example code for honeyheist
//problem at https://open.kattis.com/problems/honeyheist
#include<iostream>
#include<unordered_map>
#include<vector>

#include "graph.h"
#include "bfs.h"

int main() {
  int R,N,A,B,X;
  std::cin >> R >> N >> A >> B >> X;
  //map to whether or not a square is wax;
  std::unordered_map<int,bool> is_wax;
  int num_tiles = R*R*R-(R-1)*(R-1)*(R-1);
  for (int i = 1; i < num_tiles+1;i++) {
    is_wax[i]=false;
  }
  int temp;
  for (int i = 0 ; i < X; i++) {
    std::cin >> temp;
    is_wax[temp]=true;

  }

  Graph g(num_tiles+1);
  //for each row
  int num_tiles_seen = 1; //graph ids start at 1
  int tiles_in_row = R;
  for (int row = 0; row < 2*R-1; row++) {
  
    for (int j = 0; j < tiles_in_row; j++) {
      int tile_val = num_tiles_seen + j;
      //if we can move right
      if (j < tiles_in_row-1 && !is_wax[tile_val] && !is_wax[tile_val+1]) {
        g.add_uedge(tile_val,tile_val+1);
      }
    }
    //if we are in a row where moving down, the row size increases
    if (row < R-1) {
      for (int j = 0; j < tiles_in_row; j++) {
        int tile_val = num_tiles_seen + j;
        if (!(is_wax[tile_val]) && !(is_wax[tile_val+tiles_in_row])) {
          g.add_uedge(tile_val,tile_val+tiles_in_row);

        }
        if (!(is_wax[tile_val]) && !(is_wax[tile_val+tiles_in_row+1])) {
          g.add_uedge(tile_val,tile_val+tiles_in_row+1);

        }
       

      }
      

    }
    //if we are in a non-bottom row where moving down the row size decreases
    else if (row < 2*R-2) {
      //j=1 here
      for (int j = 1; j < tiles_in_row-1; j++) {
        int tile_val = num_tiles_seen + j;
        if (!(is_wax[tile_val]) && !(is_wax[tile_val+tiles_in_row])) {

        g.add_uedge(tile_val,tile_val+tiles_in_row);
        }
        if (!(is_wax[tile_val]) && !(is_wax[tile_val+tiles_in_row-1])) {

        g.add_uedge(tile_val,tile_val+tiles_in_row-1);
        }

      }
      //j=0 case, just add tiles_in_row
      int tile_val = num_tiles_seen;
     if (!(is_wax[tile_val]) && !(is_wax[tile_val+tiles_in_row])) {
      g.add_uedge(tile_val,tile_val+tiles_in_row);
     }
      //j=tiles_in_row-1 case, just add tiles_in_row-1
      tile_val=num_tiles_seen + tiles_in_row-1;

      if (!(is_wax[tile_val]) && !(is_wax[tile_val+tiles_in_row-1])) {
        g.add_uedge(tile_val,tile_val+tiles_in_row-1);
      }


    }

    //iterate appropriately
    num_tiles_seen += tiles_in_row;
    //calculate the # of tiles in the next row
    if (row < R-1) {
      tiles_in_row += 1;
    }
    else {
      tiles_in_row -= 1;
    }
  
    
  }

  std::vector<int> starts;
  starts.push_back(A);
  g.bfs(starts); //run the actual bfs
  if (g.nodes[B].depth <= N) {
    std::cout << g.nodes[B].depth << std::endl;
  }
  else {
    std::cout << "No" << std::endl;
  }


}