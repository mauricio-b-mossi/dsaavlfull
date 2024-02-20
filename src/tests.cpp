#include "avl.hpp"
#include <iostream>
#include <vector>

int main() {

  AVL<int, int> avl;
  std::vector<int> vec{3, 1, 4, 5, 0, 10, 2, 11, 19, 21, 35};

  for (auto num : vec) {
    avl.insert(num, num);
  }

  std::cout << "Del 0" << std::endl;
  avl.sremoveNthNode(0);
  std::cout << "Del 100" << std::endl;
  avl.sremoveNthNode(100);
  std::cout << "Del -1" << std::endl;
  avl.sremoveNthNode(-1);
  std::cout << "Del 6" << std::endl;
  avl.sremoveNthNode(6);
  std::cout << "Del 6" << std::endl;
  avl.sremoveNthNode(6);

  avl.printNodeHeights();

  return 0;
}
