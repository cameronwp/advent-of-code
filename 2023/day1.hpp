#include <iostream>
#include "day.hpp"

class Day1 : public Day {
  public:
    Day1() : Day(1) {
      std::cout << "in Day1 constructor" << std::endl;
    };
    std::string run();


};
