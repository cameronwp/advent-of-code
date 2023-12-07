#include "day.hpp"
#include <fstream>
#include <iostream>

Day::Day(int day) {
  thisDay = day;
  stream.open("data/day" + std::to_string(day) + ".txt");
}

Day::~Day() { stream.close(); }

std::string Day::nextline() {
  std::string line = uninitialized;
  std::getline(stream, line);
  return line;
}
