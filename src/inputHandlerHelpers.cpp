#include "gatorAvl.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

bool checkValidEndOfCommand(std::istringstream &iss, std::string &holder,
                            std::string &expected) {
  if (std::getline(iss, holder)) {
    std::cout << "true" << std::endl;
    return holder == expected;
  };

  return true;
};

bool checkValidEndOfCommand(std::istringstream &iss, std::string &holder,
                            std::string &&expected) {
  if (std::getline(iss, holder)) {
    std::cout << "true" << std::endl;
    return holder == expected;
  };

  return true;
};

void ltrim(std::string &s) { s.erase(0, s.find_first_not_of(" \t\n\r\f\v")); }

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

void handlePrintLevelCount(std::istringstream &iss, std::string &word,
                           GatorAvl &avl) {
  if (!checkValidEndOfCommand(iss, word, "printLevelCount")) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }
  avl.printLevelCount();
}

void handleRemoveInorder(std::istringstream &iss, std::string &word,
                         std::regex &numberRegexp, GatorAvl &avl) {
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
}
