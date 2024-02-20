#pragma once
#include "avl.hpp"

struct GatorAvl {
  // Inserts node by NAME and ID, where the ID is the key. If successful prints
  // successful, else prints unsuccessful.
  void insert(std::string name, std::string id);

  // Removes node by ID. If successful prints successful, else prints
  // unsuccessful.
  void remove(std::string id);

  // Searches student by ID. If found, prints student NAME, else prints
  // unsuccessful.
  void searchId(std::string id);

  // Searches student by NAME. If found prints student ID, if there is more
  // than one object with the same NAME both names are printed in separate
  // lines.
  void searchNames(std::string name);

  // Prints out a comma separated inorder traversal of the NAMES in the tree.
  void printInorder();

  // Prints out a comma separated preorder traversal of the NAMES in the tree.
  void printPreorder();

  // Prints out a comma separated postorder traversal of the NAMES in the tree.
  void printPostorder();

  // Prints number of levels in the tree.
  void printLevelCount();

  // Removes the Nth GatorId from the inorder traversal of the tree.
  void removeInorder(size_t index);

private:
  AVL<std::string, std::string> avl;
};
