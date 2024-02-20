#pragma once
#include <cmath>
#include <functional>
#include <iostream>

template <typename K, typename V> struct Node {
  Node(K key, V value) : key{key}, value{value} {};
  ~Node(){};

  K key;
  V value;

  Node<K, V> *l = nullptr;
  Node<K, V> *r = nullptr;

  int height = 1;
};

template <typename K, typename V> struct AVL {

  typedef std::function<void(Node<K, V> *)> nodeAction;

  AVL() {}
  ~AVL() { postorderDeallocate(root); }

  void insert(K key, V value) {
    Node<K, V> *node = new Node<K, V>(key, value);
    insert(node);
  }

  void insert(Node<K, V> *node) { root = insertHelper(root, node); }

  // Remove, if node contains two leafs, do successor removal.
  void sremove(K key) { root = deleteHelperSuccessor(root, key); };

  // Remove, if node contains two leafs, do predecessor removal.
  void premove(K key) { root = deleteHelperPredecessor(root, key); };

  void inorder(nodeAction nodeAction) { inorderHelper(root, nodeAction); }

  void postorder(nodeAction nodeAction) { postorderHelper(root, nodeAction); };

  void preorder(nodeAction nodeAction) { preorderHelper(root, nodeAction); };

  void printNodeHeights() {
    getNodeHeightsHelper(root);
    std::cout << std::endl;
  }

  int getAvlHeight() { return root ? root->height : 0; }

  void searchKey(K key) {
    Node<K, V> *node = searchKeyHelper(root, key);
    if (node == nullptr) {
      std::cout << "unsuccessful" << std::endl;
      return;
    }
    std::cout << node->value << std::endl;
  }

  void searchValues(V value) {
    unsigned char count = 0;
    searchValuesHelper(root, [value, &count](Node<K, V> *node) {
      if (node->value == value)
        std::cout << node->key << std::endl;
      count++;
    });

    if (count < 1)
      std::cout << "unsuccessful" << std::endl;
  }

private:
  Node<K, V> *root = nullptr;

  // Once rotated only the heights of the rotated values changes.
  // If single rotation 2 change (root, child).
  // If double rotation 3 change (root, child, grandchild).
  // The only heights that change are those of the rotated objects, namely,
  Node<K, V> *rotateLeft(Node<K, V> *root) {
    Node<K, V> *gp = root->r->l;
    Node<K, V> *newRoot = root->r;
    newRoot->l = root;
    root->r = gp;
    setNodeHeight(root);
    setNodeHeight(newRoot);
    return newRoot;
  }

  // This bug cost me hours, first update oldRootHeight, then newRoot, duh!
  Node<K, V> *rotateRight(Node<K, V> *root) {
    Node<K, V> *gp = root->l->r;
    Node<K, V> *newRoot = root->l;
    newRoot->r = root;
    root->l = gp;
    setNodeHeight(root);
    setNodeHeight(newRoot);
    return newRoot;
  }

  Node<K, V> *rotateLeftRight(Node<K, V> *root) {
    root->l = rotateLeft(root->l);
    return rotateRight(root);
  }

  Node<K, V> *rotateRightLeft(Node<K, V> *root) {
    root->r = rotateRight(root->r);
    return rotateLeft(root);
  }

  Node<K, V> *insertHelper(Node<K, V> *root, Node<K, V> *node) {

    if (root == nullptr) {
      return node;
    }

    if (node->key > root->key) {
      root->r = insertHelper(root->r, node);
    } else if (node->key < root->key) {
      root->l = insertHelper(root->l, node);
    } else {
      // When equal returns unsuccessful. Cannot insert duplicates.
      std::cout << "unsuccessful" << std::endl;
    }

    setNodeHeight(root);

    int rootLeftHeight = root->l ? root->l->height : 0;
    int rootRightHeight = root->r ? root->r->height : 0;

    if (std::abs(rootLeftHeight - rootRightHeight) > 1)
      return performRotation(root);

    return root;
  };

  Node<K, V> *deleteHelperSuccessor(Node<K, V> *root, K key) {

    // Perform deletion.
    if (root == nullptr) {
      std::cout << "unsuccessful" << std::endl;
      return nullptr;
    }

    // shouldn't it be key?'
    if (key == root->key) {

      // No child case.
      if (root->l == nullptr && root->r == nullptr) {
        delete root;
        return nullptr;

        // Diff case
      } else if (root->l != nullptr && root->r != nullptr) {

        Node<K, V> *successor = getSuccessor(root);

        root->key = successor->key;
        root->value = successor->value;

        root->r = deleteHelperSuccessor(root->r, successor->key);

        // One branch case.
      } else {
        if (root->l != nullptr) {
          Node<K, V> *temp = root->l;
          delete root;
          return temp;
        } else {
          Node<K, V> *temp = root->r;
          delete root;
          return temp;
        }
      }
    } else if (key > root->value) {
      root->r = deleteHelperSuccessor(root->r, key);
    } else if (key < root->value) {
      root->l = deleteHelperSuccessor(root->l, key);
    }

    setNodeHeight(root);

    int rootLeftHeight = root->l ? root->l->height : 0;
    int rootRightHeight = root->r ? root->r->height : 0;

    if (std::abs(rootLeftHeight - rootRightHeight) > 1)
      return performRotation(root);

    return root;
  }

  Node<K, V> *deleteHelperPredecessor(Node<K, V> *root, K key) {

    // Perform deletion.
    if (root == nullptr) {
      std::cout << "unsuccessful" << std::endl;
      return nullptr;
    }

    // shouldn't it be key?'
    if (key == root->key) {

      // No child case.
      if (root->l == nullptr && root->r == nullptr) {
        delete root;
        return nullptr;

        // Diff case
      } else if (root->l != nullptr && root->r != nullptr) {

        Node<K, V> *predecessor = getPredecessor(root);

        root->key = predecessor->key;
        root->value = predecessor->value;

        root->l = deleteHelperPredecessor(root->l, predecessor->key);

        // One branch case.
      } else {
        if (root->l != nullptr) {
          Node<K, V> *temp = root->l;
          delete root;
          return temp;
        } else {
          Node<K, V> *temp = root->r;
          delete root;
          return temp;
        }
      }
    } else if (key > root->value) {
      root->r = deleteHelperPredecessor(root->r, key);
    } else if (key < root->value) {
      root->l = deleteHelperPredecessor(root->l, key);
    }

    setNodeHeight(root);

    int rootLeftHeight = root->l ? root->l->height : 0;
    int rootRightHeight = root->r ? root->r->height : 0;

    if (std::abs(rootLeftHeight - rootRightHeight) > 1)
      return performRotation(root);

    return root;
  }

  Node<K, V> *performRotation(Node<K, V> *root) {
    int rootLeftHeight = root->l ? root->l->height : 0;
    int rootRightHeight = root->r ? root->r->height : 0;

    // Left heavy at root.
    if (rootLeftHeight - rootRightHeight > 1) {
      int childLeftHeight = root->l->l ? root->l->l->height : 0;
      int childRightHeight = root->l->r ? root->l->r->height : 0;

      // Left heavy at child.
      if (childLeftHeight - childRightHeight > 0) {
        return rotateRight(root);
      }
      return rotateLeftRight(root);
    }

    // Right heavy at root
    int childLeftHeight = root->r->l ? root->r->l->height : 0;
    int childRightHeight = root->r->r ? root->r->r->height : 0;

    // Left heavy at child
    if (childLeftHeight - childRightHeight > 0) {
      return rotateRightLeft(root);
    }
    return rotateLeft(root);
  }

  void inorderHelper(Node<K, V> *node, nodeAction nodeAction) {
    if (node->l)
      inorderHelper(node->l, nodeAction);
    nodeAction(node);
    if (node->r)
      inorderHelper(node->r, nodeAction);
  };

  void postorderHelper(Node<K, V> *node, nodeAction nodeAction) {
    if (node->l)
      postorderHelper(node->l, nodeAction);
    if (node->r)
      postorderHelper(node->r, nodeAction);
    nodeAction(node);
  }

  void preorderHelper(Node<K, V> *node, nodeAction nodeAction) {
    nodeAction(node);
    if (node->l)
      preorderHelper(node->l, nodeAction);
    if (node->r)
      preorderHelper(node->r, nodeAction);
  }

  void getNodeHeightsHelper(Node<K, V> *node) {
    inorderHelper(node, [](Node<K, V> *node) -> void {
      std::cout << "Value: " << node->value << " Height: " << node->height
                << std::endl;
    });
  }

  void postorderDeallocate(Node<K, V> *node) {
    if (node == nullptr)
      return;
    if (node->l)
      postorderDeallocate(node->l);
    if (node->r)
      postorderDeallocate(node->r);
    delete node;
  }

  void setNodeHeight(Node<K, V> *root) {
    root->height = 1 + std::max(root->r ? root->r->height : 0,
                                root->l ? root->l->height : 0);
  }

  Node<K, V> *getSuccessor(Node<K, V> *root) {
    return getLeftMostNode(root->r);
  }

  Node<K, V> *getPredecessor(Node<K, V> *root) {
    return getRighMostNode(root->l);
  }

  Node<K, V> *getLeftMostNode(Node<K, V> *root) {
    if (root->l != nullptr)
      return getLeftMostNode(root->l);
    return root;
  }

  Node<K, V> *getRighMostNode(Node<K, V> *root) {
    if (root->r != nullptr)
      return getRighMostNode(root->r);

    return root;
  }

  Node<K, V> *searchKeyHelper(Node<K, V> *root, K key) {
    if (root == nullptr) {
      return nullptr;
    }

    if (key > root->key) {
      return searchKeyHelper(root->r, key);
    } else if (key < root->key) {
      return searchKeyHelper(root->l, key);
    }

    // If not nullptr, not gt or ls, then this is the node.
    return root;
  };

  // Similar to search Value, but traverses the whole tree.
  Node<K, V> *searchValuesHelper(Node<K, V> *root, nodeAction nodeAction) {
    preorder(nodeAction);
  }

  // Making copy assignment and construction private to minimize double frees.
  AVL<K, V> &operator=(const AVL<K, V> &other);
  AVL<K, V>(const AVL<K, V> &other);
};
