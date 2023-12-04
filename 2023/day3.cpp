#include "day3.hpp"
#include "lib/trim.cpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*
The engineer explains that an engine part seems to be missing from the engine,
but nobody can figure out which one. If you can add up all the part numbers in
the engine schematic, it should be easy to work out which part is missing.

The engine schematic (your puzzle input) consists of a visual representation of
the engine. There are lots of numbers and symbols you don't really understand,
but apparently any number adjacent to a symbol, even diagonally, is a "part
number" and should be included in your sum. (Periods (.) do not count as a
symbol.)

Here is an example engine schematic:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, two numbers are not part numbers because they are not
adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number
is adjacent to a symbol and so is a part number; their sum is 4361.

Of course, the actual engine schematic is much larger. What is the sum of all of
the part numbers in the engine schematic?
*/

const string SYMBOLS = "!@#$%^&*()_+-=/.";

/**
 * Get the up to 8 surrounding positions
 * @param pos y, x
 */
set<pair<int, int>> get_adjacent_coords(pair<int, int> pos, int max_y,
                                        int max_x) {
  int y = pos.first;
  int x = pos.second;

  int y_plus_1 = min(max_y, y + 1);
  int y_minus_1 = max(0, y - 1);
  int x_plus_1 = min(max_x, x + 1);
  int x_minus_1 = max(0, x - 1);

  return set<pair<int, int>>{{y_minus_1, x},         {y_plus_1, x},
                             {y_minus_1, x_minus_1}, {y_plus_1, x_minus_1},
                             {y_minus_1, x_plus_1},  {y_plus_1, x_plus_1},
                             {y, x_minus_1},         {y, x_plus_1}};
}

void track_number(string number_in_progress, int x, int y, vector<int> &numbers,
                  map<int, map<int, size_t>> &y_x_numbers) {
  // we know the last number is done. save it at each of the x positions
  numbers.push_back(stoi(number_in_progress));
  size_t position_of_new_number = numbers.size() - 1;

  // initialize {y: {x: size_t}} for the y
  y_x_numbers.emplace(y, map<int, size_t>{});

  for (int i = number_in_progress.length(); i > 0; i--) {
    y_x_numbers[y][x - i] = position_of_new_number;
  }
}

string Day3::part1() {
  int sum = 0;

  // {y: {x: 123, x+1: 123, x+2: 123}}
  map<int, map<int, size_t>> y_x_numbers;
  vector<pair<int, int>> y_x_symbols;
  // track a list of all the numbers. when we sum numbers, so long as we don't
  // sum the same position twice, we won't double count them (unless two symbols
  // are adjacent to the same number, which the puzzle input doesn't appear to
  // have)
  vector<int> numbers;

  int y = 0;
  int max_x = 0;
  int max_y = 0;
  for (string line; (line = nextline()) != "";) {
    string number_in_progress = "";

    for (int x = 0; x < line.size(); x++) {
      if (y == 0) {
        max_x = max(max_x, x);
      }

      if (SYMBOLS.find(line[x]) != string::npos) {
        if (number_in_progress != "") {
          // // we know the last number is done. save it at each of the x
          // positions
          track_number(number_in_progress, x, y, numbers, y_x_numbers);
        }

        if (line[x] != '.') {
          y_x_symbols.push_back(pair<int, int>{y, x});
        }

        number_in_progress = "";
        continue;
      }

      // must be a number
      number_in_progress.push_back(line[x]);
    }

    // we're at the end of the line. we could have a number!
    if (number_in_progress != "") {
      track_number(number_in_progress, max_x, y, numbers, y_x_numbers);
    }

    y++;
  }

  max_y = y - 1;

  // now compare the symbol adjacents to the list of numbers. find the set of
  // all number indices that match the adjacent coords
  set<size_t> numbers_to_sum;

  for (int i = 0; i < y_x_symbols.size(); i++) {
    set<pair<int, int>> adjacents =
        get_adjacent_coords(y_x_symbols[i], max_y, max_x);

    for (auto &adjacent : adjacents) {
      int y = adjacent.first;
      int x = adjacent.second;

      if (y_x_numbers.find(y) != y_x_numbers.end()) {
        if (y_x_numbers[y].find(x) != y_x_numbers[y].end()) {
          numbers_to_sum.insert(y_x_numbers[y][x]);
        }
      }
    }
  }

  for (auto &i : numbers_to_sum) {
    sum += numbers[i];
  }

  return to_string(sum);
}

/*
The missing part wasn't the only issue - one of the gears in the engine is
wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its
gear ratio is the result of multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and add them all up so
that the engineer can figure out which gear needs to be replaced.

Consider the same engine schematic again:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, there are two gears. The first is in the top left; it has
part numbers 467 and 35, so its gear ratio is 16345. The second gear is in the
lower right; its gear ratio is 451490. (The * adjacent to 617 is not a gear
because it is only adjacent to one part number.) Adding up all of the gear
ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?
*/

string Day3::part2() {
  int sum = 0;

  // {y: {x: 123, x+1: 123, x+2: 123}}
  map<int, map<int, size_t>> y_x_numbers;
  vector<pair<int, int>> y_x_gears;
  vector<int> numbers;

  int y = 0;
  int max_x = 0;
  int max_y = 0;
  for (string line; (line = nextline()) != "";) {
    string number_in_progress = "";

    for (int x = 0; x < line.size(); x++) {
      if (y == 0) {
        max_x = max(max_x, x);
      }

      if (SYMBOLS.find(line[x]) != string::npos) {
        if (number_in_progress != "") {
          // // we know the last number is done. save it at each of the x
          // positions
          track_number(number_in_progress, x, y, numbers, y_x_numbers);
        }

        if (line[x] == '*') {
          y_x_gears.push_back(pair<int, int>{y, x});
        }

        number_in_progress = "";
        continue;
      }

      // must be a number
      number_in_progress.push_back(line[x]);
    }

    // we're at the end of the line. we could have a number!
    if (number_in_progress != "") {
      track_number(number_in_progress, max_x, y, numbers, y_x_numbers);
    }

    y++;
  }

  max_y = y - 1;

  vector<int> numbers_to_sum;

  for (int i = 0; i < y_x_gears.size(); i++) {
    set<pair<int, int>> adjacents =
        get_adjacent_coords(y_x_gears[i], max_y, max_x);

    set<size_t> adjacents_found;

    // find gears that have exactly two adjacents
    for (auto &adjacent : adjacents) {
      int y = adjacent.first;
      int x = adjacent.second;

      if (y_x_numbers.find(y) != y_x_numbers.end()) {
        if (y_x_numbers[y].find(x) != y_x_numbers[y].end()) {
          adjacents_found.insert(y_x_numbers[y][x]);
        }
      }
    }

    if (adjacents_found.size() != 2) {
      continue;
    }

    // multiply the adjancents
    int multiplied = 1;
    for (auto &num_index : adjacents_found) {
      multiplied *= numbers[num_index];
    }

    numbers_to_sum.push_back(multiplied);
  }

  for (auto &gear : numbers_to_sum) {
    sum += gear;
  }

  return to_string(sum);
}

/** Run the day's problems */
void Day3::run(int part) {
  cout << "Day " << thisDay;
  if (part == 1) {
    cout << " part 1: " << part1() << endl;
  } else {
    cout << " part 2: " << part2() << endl;
  };
}
