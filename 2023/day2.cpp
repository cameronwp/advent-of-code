#include "day2.hpp"
#include <iostream>
#include <vector>

/*

*/

std::string Day2::part1() {
  std::string line;
  while ((line = nextline()) != "") {
    // probably solution here
  }
  return "";
}

/*

*/

std::string Day2::part2() {
  std::string line;
  while ((line = nextline()) != "") {
    // solution
  }
  return "";
}

/** Run the day's problems */
void Day2::run(int part) {
  if (part != 1 && part != 2) {
    std::cout << "--part must be 1 or 2" << std::endl;
  }

  std::cout << "Day " << thisDay;
  if (part == 1) {
    std::cout << " part 1: " << part1() << std::endl;
  } else {
    std::cout << " part 2: " << part2() << std::endl;
  };
}
