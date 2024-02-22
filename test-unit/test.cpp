#include <algorithm>
#include <stdexcept>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "../src/avl.hpp"
#include "../src/gatorAvl.hpp"
#include "../src/inputHandler.hpp"

/*
        To check output (At the Project1 directory):
                g++ -std=c++14 -Werror -Wuninitialized -o build/test
   test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]") {

  std::stringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  AVL<int, int> tree; // Create a Tree object
  tree.insert(3, 3);
  tree.insert(2, 2);
  tree.insert(1, 2);
  std::vector<int> actualOutput = tree.getInorderKey();
  std::vector<int> expectedOutput = {1, 2, 3};
  REQUIRE(expectedOutput.size() == actualOutput.size());
  REQUIRE(actualOutput == expectedOutput);

  actualOutput.clear();
  tree.clear();

  REQUIRE(tree.size() == actualOutput.size());

  tree.insert(3, 3);
  tree.insert(2, 2);
  tree.insert(1, 2);

  tree.inorder([&actualOutput](Node<int, int> *node) {
    actualOutput.push_back(node->key);
  });

  REQUIRE(expectedOutput.size() == actualOutput.size());
  REQUIRE(actualOutput == expectedOutput);

  // Restore the original cout
  std::cout.rdbuf(oldCout);
}

TEST_CASE("Input Handler Incorrect Commands") {

  // Simulate user input
  std::string input =
      "5\ninsert \"12345678\" 12345678\nremove 1\nsearch 10\nremoveInorder "
      "1\ninsert \"Maur12cio\" 12345678";

  std::istringstream iss(input);
  std::streambuf *oldCin = std::cin.rdbuf(iss.rdbuf());

  std::stringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  inputHandler();

  // Restore the original cout
  std::cout.rdbuf(oldCout);
  // Restore the original cin
  std::cin.rdbuf(oldCin);

  // Test the result
  REQUIRE(
      buffer.str() ==
      "unsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\n");
}

TEST_CASE("BST Edge Cases", "[flag]") {
  // Redirect cout to a stringstream
  std::stringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  // Call the function that writes to cout
  AVL<std::string, float> tree;

  tree.sremove("gonna fail");

  REQUIRE(buffer.str() == "unsuccessful\n");
  REQUIRE(tree.size() == 0);

  tree.insert("Peter", 21.5f);

  REQUIRE(buffer.str() == "unsuccessful\nsuccessful\n");
  REQUIRE(tree.size() == 1);

  tree.searchKey("John");

  REQUIRE(buffer.str() == "unsuccessful\nsuccessful\nunsuccessful\n");

  REQUIRE_THROWS_AS(tree.premoveNthNode(1), std::out_of_range);

  // Restore the original cout
  std::cout.rdbuf(oldCout);
}

TEST_CASE("BST All Rotations", "[flag]") {
  // Redirect cout to a stringstream
  std::stringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  // Call the function that writes to cout
  AVL<int, int> tree;

  std::vector<int> expectedOutput = {1, 10, 11, 40, 69, 70, 100};
  std::vector<int> actualOutput{};

  actualOutput.clear();
  tree.clear();

  REQUIRE(tree.size() == actualOutput.size());

  tree.insert(40, 40);
  tree.insert(70, 70);
  tree.insert(10, 10);
  tree.insert(11, 11);
  tree.insert(69, 69);
  tree.insert(100, 100);
  tree.insert(1, 1);

  tree.inorder([&actualOutput](Node<int, int> *node) {
    actualOutput.push_back(node->key);
  });

  REQUIRE(actualOutput == expectedOutput);

  tree.sremove(40);

  auto it = std::find(expectedOutput.begin(), expectedOutput.end(), 40);

  expectedOutput.erase(it);
  actualOutput.clear();

  tree.inorder([&actualOutput](Node<int, int> *node) {
    actualOutput.push_back(node->key);
  });

  REQUIRE(tree.size() == expectedOutput.size());
  REQUIRE(actualOutput == expectedOutput);

  // Right Left
  tree.insert(90, 90);
  expectedOutput.push_back(90);

  std::sort(expectedOutput.begin(), expectedOutput.end());

  actualOutput.clear();

  tree.inorder([&actualOutput](Node<int, int> *node) {
    actualOutput.push_back(node->key);
  });

  REQUIRE(tree.size() == expectedOutput.size());
  REQUIRE(actualOutput == expectedOutput);

  // Right Right
  tree.insert(-1, -1);
  expectedOutput.push_back(-1);
  tree.insert(50, 50);
  expectedOutput.push_back(50);
  tree.insert(60, 60);
  expectedOutput.push_back(60);

  std::sort(expectedOutput.begin(), expectedOutput.end());

  actualOutput.clear();

  tree.inorder([&actualOutput](Node<int, int> *node) {
    actualOutput.push_back(node->key);
  });

  REQUIRE(tree.size() == expectedOutput.size());
  REQUIRE(actualOutput == expectedOutput);

  // Left Left
  tree.insert(800, 800);
  expectedOutput.push_back(800);
  tree.insert(5000, 5000);
  expectedOutput.push_back(5000);

  std::sort(expectedOutput.begin(), expectedOutput.end());

  actualOutput.clear();

  tree.inorder([&actualOutput](Node<int, int> *node) {
    actualOutput.push_back(node->key);
  });

  REQUIRE(tree.size() == expectedOutput.size());
  REQUIRE(actualOutput == expectedOutput);

  // Left Right
  tree.insert(0, 0);
  expectedOutput.push_back(0);

  actualOutput.clear();

  tree.inorder([&actualOutput](Node<int, int> *node) {
    actualOutput.push_back(node->key);
  });

  std::sort(expectedOutput.begin(), expectedOutput.end());

  REQUIRE(tree.size() == expectedOutput.size());
  REQUIRE(actualOutput == expectedOutput);

  tree.clear();

  REQUIRE(tree.size() == 0);

  // Restore the original cout
  std::cout.rdbuf(oldCout);
}

TEST_CASE("BST Test All Deletions", "[flag]") {

  std::stringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  AVL<int, int> tree;
  std::vector<int> expectedOutput = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i : expectedOutput) {
    tree.insert(i, i);
  }

  REQUIRE(expectedOutput == tree.getInorderKey());

  // Removes top, two children case.
  tree.sremove(4);

  expectedOutput.erase(
      std::find(expectedOutput.begin(), expectedOutput.end(), 4));
  std::sort(expectedOutput.begin(), expectedOutput.end());

  REQUIRE(expectedOutput == tree.getInorderKey());

  // Removes top again, two children case.
  tree.sremove(5);

  expectedOutput.erase(
      std::find(expectedOutput.begin(), expectedOutput.end(), 5));
  std::sort(expectedOutput.begin(), expectedOutput.end());

  REQUIRE(expectedOutput == tree.getInorderKey());

  // Removes parent with single child, 1 child case.
  tree.sremove(9);

  expectedOutput.erase(
      std::find(expectedOutput.begin(), expectedOutput.end(), 9));
  std::sort(expectedOutput.begin(), expectedOutput.end());

  REQUIRE(expectedOutput == tree.getInorderKey());

  // Removes leaf, 0 child case.
  tree.sremove(10);

  expectedOutput.erase(
      std::find(expectedOutput.begin(), expectedOutput.end(), 10));
  std::sort(expectedOutput.begin(), expectedOutput.end());

  REQUIRE(expectedOutput == tree.getInorderKey());

  // Restore the original cout
  std::cout.rdbuf(oldCout);
}

TEST_CASE("BST Insert 1000  Remove 100", "[flag]") {

  std::stringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  AVL<int, int> tree;
  std::vector<int> expectedOutput;

  // In that confident
  for (int i = 0; i < 1000; i++) {
    int randomInput = rand();
    if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) ==
        0) {
      expectedOutput.push_back(i);
      tree.insert(i, i);
    }
  }

  for (int i = 0; i < 100; i++) {
    int minValue = 0;
    int maxValue = expectedOutput.size() - 1;

    int randomInput = rand() % (maxValue - minValue + 1) + minValue;

    if (randomInput < expectedOutput.size()) {
      expectedOutput.erase(
          std::find(expectedOutput.begin(), expectedOutput.end(), i));

      tree.sremove(i);
    }
  }

  std::sort(expectedOutput.begin(), expectedOutput.end());

  REQUIRE(expectedOutput == tree.getInorderKey());

  // Restore the original cout
  std::cout.rdbuf(oldCout);
}
