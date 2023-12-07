#include "day.hpp"
#include <iostream>

class Day5 : public Day {
public:
  Day5() : Day(5){};
  void run(int part);
  std::string part1();
  std::string part2();
};
