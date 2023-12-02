#include "day.hpp"
#include <iostream>

class Day2 : public Day {
public:
  Day2() : Day(2){};
  void run(int part);
  std::string part1();
  std::string part2();
};
