#pragma once
#include <sstream>
#include <string>

bool checkValidEndOfCommand(std::istringstream &iss, std::string &holder,
                            std::string &expected);

bool checkValidEndOfCommand(std::istringstream &iss, std::string &holder,
                            std::string &&expected);

void ltrim(std::string &s);
