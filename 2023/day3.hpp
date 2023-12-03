#include "day.hpp"
#include <iostream>

class Day3 : public Day {
public:
  Day3() : Day(3){};
  void run(int part);
  std::string part1();
  std::string part2();
};
