#include <iostream>
#include <fstream>
#include "day.hpp"


Day::Day(int day) {
  thisDay = day;
  stream.open("data/day" + std::to_string(day) + ".txt");
}

Day::~Day() {
  stream.close();
}

std::string Day::nextline() {
  std::string line;
  std::getline(stream, line);
  return line;
}
