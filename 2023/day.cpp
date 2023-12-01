#include <iostream>
#include <fstream>
#include "day.hpp"

Day::Day(int day) {
  std::cout << "in Day constructor" << std::endl;
  // std::ifstream file("data/day" + std::to_string(day) + ".txt");
}

std::string Day::nextLine() {
  std::string line;
  // std::getline(file, line);
  return line;
}
