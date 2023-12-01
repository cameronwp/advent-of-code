#pragma once

#include <fstream>
#include <iostream>

// FYI file stream handling technique from here: https://stackoverflow.com/a/18522214

class Day {
  public:
    Day(int day);
    ~Day();
    std::string run();
    std::string nextline();

  private:
    Day(Day&);
    void operator= (Day&);

    // the file stream
    std::ifstream stream;
};
