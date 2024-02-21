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

    if (word == "insert") {
      std::getline(iss, word, '\"');
      std::getline(iss, word, '\"');

      if (!std::regex_match(word, nameRegexp)) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }

      std::string name{word};

      iss >> word;

      if (!std::regex_match(word, idRegexp)) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }

      std::string id{word};

      if (!checkValidEndOfCommand(iss, word, id)) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }

      // Call avl.insert.
      avl.insert(name, id);

    } else if (word == "remove") {
      iss >> word;

      if (!std::regex_match(word, idRegexp)) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }

      std::string id{word};

      if (!checkValidEndOfCommand(iss, word, id)) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }

      // Call avl.remove.
      avl.remove(id);

    } else if (word == "search") {

      std::getline(iss, word, '\"');

      if (std::getline(iss, word, '\"')) {

        if (!std::regex_match(word, nameRegexp)) {
          std::cout << "unsuccessful" << std::endl;
          return;
        }

        std::string name{word};

        if (!checkValidEndOfCommand(iss, word, name)) {
          std::cout << "unsuccessful" << std::endl;
          return;
        }

        // Call search name.
        avl.searchNames(name);

      } else {

        ltrim(word);

        if (!std::regex_match(word, idRegexp)) {
          std::cout << "unsuccessful" << std::endl;
          return;
        };

        std::string id{word};

        if (!checkValidEndOfCommand(iss, word, id)) {
          std::cout << "threw" << std::endl;
          std::cout << "unsuccessful" << std::endl;
          return;
        }

        // Call search Id.
        avl.searchId(id);
      }

    } else if (word == "printInorder") {

      if (!checkValidEndOfCommand(iss, word, "printInorder")) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }
      avl.printInorder();

    } else if (word == "printPreorder") {

      if (!checkValidEndOfCommand(iss, word, "printPreorder")) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }
      avl.printPreorder();

    } else if (word == "printPostorder") {

      if (!checkValidEndOfCommand(iss, word, "printPostorder")) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }
      avl.printPostorder();

    } else if (word == "printLevelCount") {

      if (!checkValidEndOfCommand(iss, word, "printLevelCount")) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }
      avl.printLevelCount();

    } else if (word == "removeInorder") {
      iss >> word;

      if (!std::regex_match(word, numberRegexp)) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }

      std::string nstr{word};

      if (!checkValidEndOfCommand(iss, word, nstr)) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }

      size_t n = std::stoi(nstr);

      if (n < 0) {
        std::cout << "unsuccessful" << std::endl;
        return;
      }

      avl.removeInorder(n);

    } else {
      std::cout << "unsuccessful" << std::endl;
      return;
    }
  }
}

void handleInsert(std::istringstream &iss, std::string &word,
                  std::regex &nameRegexp, std::regex &idRegexp, GatorAvl &avl) {
  std::getline(iss, word, '\"');
  std::getline(iss, word, '\"');

  if (!std::regex_match(word, nameRegexp)) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  std::string name{word};

  iss >> word;

  if (!std::regex_match(word, idRegexp)) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  std::string id{word};

  if (!checkValidEndOfCommand(iss, word, id)) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  // Call avl.insert.
  avl.insert(name, id);
}

void handleRemove(std::istringstream &iss, std::string &word,
                  std::regex &idRegexp, GatorAvl &avl) {
  iss >> word;

  if (!std::regex_match(word, idRegexp)) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  std::string id{word};

  if (!checkValidEndOfCommand(iss, word, id)) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  // Call avl.remove.
  avl.remove(id);
}

void handleSearch(std::istringstream &iss, std::string &word,
                  std::regex &nameRegexp, std::regex &idRegexp, GatorAvl &avl) {
  std::getline(iss, word, '\"');

  if (std::getline(iss, word, '\"')) {

    if (!std::regex_match(word, nameRegexp)) {
      std::cout << "unsuccessful" << std::endl;
      return;
    }

    std::string name{word};

    if (!checkValidEndOfCommand(iss, word, name)) {
      std::cout << "unsuccessful" << std::endl;
      return;
    }

    // Call search name.
    avl.searchNames(name);

  } else {

    ltrim(word);

    if (!std::regex_match(word, idRegexp)) {
      std::cout << "unsuccessful" << std::endl;
      return;
    };

    std::string id{word};

    if (!checkValidEndOfCommand(iss, word, id)) {
      std::cout << "threw" << std::endl;
      std::cout << "unsuccessful" << std::endl;
      return;
    }

    // Call search Id.
    avl.searchId(id);
  }
}

void handlePrintInoder(std::istringstream &iss, std::string &word,
                       GatorAvl &avl) {
  if (!checkValidEndOfCommand(iss, word, "printInorder")) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }
  avl.printInorder();
}

void handlePostorder(std::istringstream &iss, std::string &word,
                     GatorAvl &avl) {
  if (!checkValidEndOfCommand(iss, word, "printPostorder")) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }
  avl.printPostorder();
}

void handlePrintPreorder(std::istringstream &iss, std::string &word,
                         GatorAvl &avl) {
  if (!checkValidEndOfCommand(iss, word, "printPreorder")) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }
  avl.printPreorder();
}
