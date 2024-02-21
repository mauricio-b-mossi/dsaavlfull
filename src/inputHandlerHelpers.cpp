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
