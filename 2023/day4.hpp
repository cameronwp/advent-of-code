#include "day.hpp"
#include <iostream>

class Day4 : public Day {
public:
  Day4() : Day(4){};
  void run(int part);
  std::string part1();
  std::string part2();
};
