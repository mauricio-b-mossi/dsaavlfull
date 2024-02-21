#include <iostream>
#include <istream>
#include <regex>
#include <sstream>
#include <string>

#include "gatorAvl.hpp"
#include "inputHandlerHelpers.hpp"

void inputHandler() {

  GatorAvl avl;

  std::regex idRegexp("\\b\\d{8}\\b");

  std::regex nameRegexp("^[A-Za-z ]+$");

  std::regex numberRegexp("^\\d+$");

  int numCommands;

  std::cin >> numCommands;

  if (std::cin.fail()) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  std::cin.ignore();

  for (size_t i = 0; i < numCommands; i++) {
    std::string line;

    std::getline(std::cin, line);

    std::istringstream iss{line};

    std::string word;

    // >> Does skip leading white space. getline doesn't.
    iss >> word;

    if (word == "insert")
      handleInsert(iss, word, nameRegexp, idRegexp, avl);
    else if (word == "remove")
      handleRemove(iss, word, idRegexp, avl);
    else if (word == "search")
      handleSearch(iss, word, nameRegexp, idRegexp, avl);
    else if (word == "printInorder")
      handlePrintInoder(iss, word, avl);
    else if (word == "printPreorder")
      handlePrintPreorder(iss, word, avl);
    else if (word == "printPostorder")
      handlePostorder(iss, word, avl);
    else if (word == "printLevelCount")
      handlePrintLevelCount(iss, word, avl);
    else if (word == "removeInorder") {
      handleRemoveInorder(iss, word, numberRegexp, avl);
    } else {
      std::cout << "unsuccessful" << std::endl;
    }
  }
}
