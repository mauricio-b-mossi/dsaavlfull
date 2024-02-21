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

void GatorAvl::remove(std::string id) { avl.sremove(id); }

void GatorAvl::searchId(std::string id) { avl.searchKey(id); }

void GatorAvl::searchNames(std::string name) { avl.searchValues(name); }

void GatorAvl::printInorder() {
  if (avl.size() > 0) {
    avl.inorder([](Node<std::string, std::string> *node) {
      std::cout << node->value << ", ";
    });
    std::cout << std::endl;
  }
};

void GatorAvl::printPreorder() {
  if (avl.size() > 0) {
    avl.preorder([](Node<std::string, std::string> *node) {
      std::cout << node->value << ", ";
    });
    std::cout << std::endl;
  }
};

void GatorAvl::printPostorder() {
  if (avl.size() > 0) {
    avl.postorder([](Node<std::string, std::string> *node) {
      std::cout << node->value << ", ";
    });
    std::cout << std::endl;
  }
};

void GatorAvl::printLevelCount() {
  std::cout << avl.getAvlHeight() << std::endl;
};

void GatorAvl::removeInorder(size_t index) { avl.sremoveNthNode(index); };
