#pragma once
#include "gatorAvl.hpp"
#include <regex>
#include <sstream>
#include <string>

bool checkValidEndOfCommand(std::istringstream &iss, std::string &holder,
                            std::string &expected);

bool checkValidEndOfCommand(std::istringstream &iss, std::string &holder,
                            std::string &&expected);

void ltrim(std::string &s);

void handleInsert(std::istringstream &iss, std::string &word,
                  std::regex &nameRegexp, std::regex &idRegexp, GatorAvl &avl);

void handleRemove(std::istringstream &iss, std::string &word,
                  std::regex &idRegexp, GatorAvl &avl);

void handleSearch(std::istringstream &iss, std::string &word,
                  std::regex &nameRegexp, std::regex &idRegexp, GatorAvl &avl);

void handlePrintInoder(std::istringstream &iss, std::string &word,
                       GatorAvl &avl);

void handlePostorder(std::istringstream &iss, std::string &word, GatorAvl &avl);

void handlePrintPreorder(std::istringstream &iss, std::string &word,
                         GatorAvl &avl);

void handlePrintLevelCount(std::istringstream &iss, std::string &word,
                           GatorAvl &avl);

void handleRemoveInorder(std::istringstream &iss, std::string &word,
                         std::regex &numberRegexp, GatorAvl &avl);
