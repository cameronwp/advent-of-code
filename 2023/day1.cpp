#include "day1.hpp"
#include <iostream>
#include <vector>

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

bool is_number(char c) {
  int x = c;
  return x >= 48 && x <= 57;
}

std::string Day1::part1() {
  int sum = 0;

  std::string line;
  while ((line = nextline()) != "") {
    int line_len = line.length();
    int first = -1;
    int last = 0;

    for (char &c : line) {
      if (!is_number(c)) {
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

/*
Your calculation isn't quite right. It looks like some of the digits are
actually spelled out with letters: one, two, three, four, five, six, seven,
eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and last
digit on each line. For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen

In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76.
Adding these together produces 281.

What is the sum of all of the calibration values?
*/

/**
 * Return -1 if no word is found
 */
int find_number_in_words(char c, std::vector<std::string> *maybe_words) {
  std::vector<std::string> number_words{"zero",  "one",  "two", "three",
                                        "four",  "five", "six", "seven",
                                        "eight", "nine"};

  // grow all word strings
  for (std::string &maybe_word : *maybe_words) {
    maybe_word.push_back(c);
  }

  // and make a new word string starting with this char
  std::string new_word(1, c);
  maybe_words->push_back(new_word);

  // check if any word string matches a number
  for (std::string &maybe_word : *maybe_words) {
    for (int i = 0; i < number_words.size(); i++) {
      if (maybe_word == number_words[i]) {

        // as pointed out on reddit:
        // "The right calibration values for string "eighthree" is 83 and for
        // "sevenine" is 79."

        // so we can still clear everything...
        maybe_words->clear();

        // ... but we should keep the character we just got
        std::string new_word(1, c);
        maybe_words->push_back(new_word);

        return i;
      }
    }
  }

  return -1;
}

std::string Day1::part2() {
  int sum = 0;

  std::string line;
  while ((line = nextline()) != "") {
    int line_len = line.length();
    int first = -1;
    int last = 0;

    std::vector<std::string> maybe_words;

    for (char &c : line) {
      int x;
      if (!is_number(c)) {
        x = find_number_in_words(c, &maybe_words);
        if (x < 0) {
          continue;
        }
      } else {
        x = c;
        // 0 is 48 in ascii
        x -= 48;
      }

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

/** Run the day's problems */
void Day1::run(int part) {
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
