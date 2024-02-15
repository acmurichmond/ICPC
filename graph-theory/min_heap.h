//making a min heap, for Dijkstra's algorithm
//developing from Figure 4.16, Dasgupta's Algorithms
//need to switch parameters into correct order**
#include<vector>
#include<unordered_map>
#include<iostream>
#include<limits>
struct MinHeap {

  typedef long long ll;

  std::vector<int> h;
  std::unordered_map<int,ll> key;
  std::unordered_map<int,int> pos;
  
  void insert(int x,ll key_val) {
    key[x]=key_val;
    h.push_back(x);
    bubble_up(x,h.size()-1);
  }

  //decrease key in min heap. Returns true if the new key actually less than the old key
  bool decrease_key(int x, ll new_key_val) {
    if (new_key_val < key[x]) { //only decrease key if new value is lower
      key[x] = new_key_val;
      bubble_up(x,pos[x]);
      return true;
    }
    return false;
    
  }
  int delete_min() {
    if (h.size()==0) {
      //TODO abort here?
      std::cout << "error, removing element from empty heap" << std::endl;
      exit(3);
      return -1;
    }
    int x = h[0];
    int insert_val = h[h.size()-1];

    h.pop_back(); //remove as to not double add
    pos[x]=-1; //x has been removed, no pos
    sift_down(insert_val,0);
    return x;
    

  }

  MinHeap() {}


  void bubble_up(int x, int i) {
    int p = (i-1)/2; //(i+1)/2 equal to ceil(i/2.0)
    while (i != 0 && key[h[p]] > key[x]) {
      h[i]=h[p];
      pos[h[p]]=i;
      i=p;
      p=(i-1)/2;
      
    }
    h[i]=x;
    pos[x]=i;


  }
  void sift_down(int x, int i) {
    // std::cout << "sifting down " << x << " " << i << std::endl;
    int c = min_child(i);
   // std::cout << "min child is  " << c << std::endl;
    while (c != 0 && key[h[c]] < key[x]) {
      h[i]=h[c];
      pos[h[c]]=i; 
      i=c; 
      c = min_child(i);
    }
    h[i]=x;
    pos[x]=i;

  }

  int min_child(int i) {
    if (2 * i + 1 >= h.size()) return 0; //no children
    else {
      ll min_val = std::numeric_limits<ll>::max();
      int min_index=2*i+1;
      for (int j = 2 * i+1; j <= std::min(h.size()-1,static_cast<size_t>(2*i+2)); j++) {
        if (key[h[j]] < min_val) {
          min_val=key[h[j]];
          min_index=j;
        }

      }
      return min_index;

    }

  }

  bool empty() {
    return h.size() == 0;
  }

  void print() {
    std::cout << "printing heap: " << std::endl;
    for (int i = 0; i < h.size(); i++) {
      std::cout << h[i] << " ";
    }
    std::cout << std::endl << std::endl;
    std::cout << "printing pos " << std::endl;
    for (auto iter = pos.begin(); iter != pos.end(); iter++) {
      std::cout << iter->first << " " << iter->second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "printing key " << std::endl;
    for (auto iter = key.begin(); iter != key.end(); iter++) {
      std::cout << iter->first << " " << iter->second << std::endl;
    }
    std::cout << std::endl;
  }


};