#include "day1.hpp"
#include <iostream>

/*
The newly-improved calibration document consists of lines of text; each line
originally contained a specific calibration value that the Elves now need to
recover. On each line, the calibration value can be found by combining the first
digit and the last digit (in that order) to form a single two-digit number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet

In this example, the calibration values of these four lines are 12, 38, 15,
and 77. Adding these together produces 142.

Consider your entire calibration document. What is the sum of all of the
calibration values?
*/

bool isNumber(char c) {
  int x = c;
  return x >= 48 && x <= 57;
}

/** Run the day's problem */
std::string Day1::run() {
  int sum = 0;

  std::string line;
  while ((line = nextline()) != "") {
    int line_len = line.length();
    int first = -1;
    int last = 0;

    for (char &c : line) {
      if (!isNumber(c)) {
        continue;
      }

      int x = c;
      // 0 is 48 in ascii
      x -= 48;

      if (first == -1) {
        // first digit is the tens place
        first = x * 10;
        // if there is no second digit for the ones, use the first again
        last = x;
      } else {
        last = x;
      }
    }

    sum += first + last;
  }
  return std::to_string(sum);
}
