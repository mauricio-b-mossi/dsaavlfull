#include "gatorAvl.hpp"
#include <regex>

void GatorAvl::insert(std::string name, std::string id) {
  // Perform string validation.
  /*
   * Validation Rules:
   * - UFID are strictly 8 digits long and must be unique (uniqueness is
   * handled by insert). \d{8}.
   * - Names must be all alphanumeric and spaces, no upper bound.
   */

  std::regex idRegexp("\\b\\d{8}\\b");

  std::regex nameRegexp("^[A-Za-z ]+$");

  if (!std::regex_match(name, nameRegexp)) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  if (!std::regex_match(id, idRegexp)) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  avl.insert(id, name);
};

void GatorAvl::remove(std::string id) {
  if (avl.size() < 1) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }
  avl.sremove(id);
}

void GatorAvl::searchId(std::string id) {
  if (avl.size() < 1) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }
  avl.searchKey(id);
}

void GatorAvl::searchNames(std::string name) {

  if (avl.size() < 1) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }
  avl.searchValues(name);
}

void GatorAvl::printInorder() {
  int count = 0;
  int size = avl.size();
  if (avl.size() > 0) {
    avl.inorder([&count, size](Node<std::string, std::string> *node) {
      std::cout << node->value;
      if (++count != size)
        std::cout << ", ";
    });
    std::cout << std::endl;
  }
};

void GatorAvl::printPreorder() {
  int count = 0;
  int size = avl.size();
  if (avl.size() > 0) {
    avl.preorder([&count, size](Node<std::string, std::string> *node) {
      std::cout << node->value;
      if (++count != size)
        std::cout << ", ";
    });
    std::cout << std::endl;
  }
};

void GatorAvl::printPostorder() {
  int count = 0;
  int size = avl.size();
  if (avl.size() > 0) {
    avl.postorder([&count, size](Node<std::string, std::string> *node) {
      std::cout << node->value;
      if (++count != size)
        std::cout << ", ";
    });
    std::cout << std::endl;
  }
};

void GatorAvl::printLevelCount() {
  std::cout << avl.getAvlHeight() << std::endl;
};

void GatorAvl::removeInorder(size_t index) {
  if (avl.size() < 1) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }
  avl.sremoveNthNode(index);
};
