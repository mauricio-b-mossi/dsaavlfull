#include "avl.hpp"

int main() {
  AVL<int, int> avl;
  for (size_t i = 0; i < 10; i++) {
    avl.insert(i, i);
  }
  avl.getHeights();
}
