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
  avl.sremove(3);
  avl.sremove(2);
  avl.sremove(0);
  avl.sremove(10);
  avl.sremove(19);
  avl.sremove(4);

  std::cout << "Loading" << std::endl;

  avl.printNodeHeights();
  std::cout << "Loading" << std::endl;

  return 0;
}
