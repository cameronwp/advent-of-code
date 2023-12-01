#include "day.hpp"
#include <iostream>

class Day1 : public Day {
public:
  Day1() : Day(1){};
  void run(int part);
  std::string part1();
  std::string part2();
};
