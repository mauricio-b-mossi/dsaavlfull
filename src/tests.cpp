#include "avl.hpp"
#include <iostream>
#include <vector>

int main() {

  AVL<int, int> avl;
  std::vector<int> vec{3, 1, 4, 5, 0, 10, 2, 11, 19, 21, 35};

  for (auto num : vec) {
    avl.insert(num, num);
  }

  std::cout << "Loading" << std::endl;
  avl.sremove(20);
  avl.sremove(100);
  avl.sremove(111);
  avl.sremove(6);
  avl.sremove(27);
  avl.sremove(222);

  std::cout << "Loading" << std::endl;

  avl.printNodeHeights();
  std::cout << "Loading" << std::endl;

  return 0;
}
