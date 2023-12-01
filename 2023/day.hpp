#pragma once

#include <fstream>
#include <iostream>

class Day {
  public:
    Day(int day);
    std::string run();

  private:
    int dayOfMonth;
    std::ifstream file;
    std::string nextLine();
};
