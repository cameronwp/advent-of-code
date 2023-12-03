#include "day2.hpp"
#include "lib/trim.cpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
To get information, once a bag has been loaded with cubes, the Elf will reach
into the bag, grab a handful of random cubes, show them to you, and then put
them back in the bag. He'll do this a few times per game.

You play several games and record the information from each game (your puzzle
input). Each game is listed with its ID number (like the 11 in Game 11: ...)
followed by a semicolon-separated list of subsets of cubes that were revealed
from the bag (like 3 red, 5 green, 4 blue).

For example, the record of a few games might look like this:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

In game 1, three sets of cubes are revealed from the bag (and then put back
again). The first set is 3 blue cubes and 4 red cubes; the second set is 1 red
cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green cubes.

The Elf would first like to know which games would have been possible if the bag
contained only 12 red cubes, 13 green cubes, and 14 blue cubes?

In the example above, games 1, 2, and 5 would have been possible if the bag had
been loaded with that configuration. However, game 3 would have been impossible
because at one point the Elf showed you 20 red cubes at once; similarly, game 4
would also have been impossible because the Elf showed you 15 blue cubes at
once. If you add up the IDs of the games that would have been possible, you
get 8.

Determine which games would have been possible if the bag had been loaded with
only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the IDs
of those games?
*/

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;

bool is_valid_cube_set(string color_count) {
  int i = 0;
  int count;

  trim(color_count);

  istringstream input;
  input.str(color_count);
  for (string element; getline(input, element, ' ');) {
    if (i == 0) {
      count = stoi(element);
      i++;
      continue;
    }

    if (element == "red") {
      return count <= MAX_RED;
    }
    if (element == "green") {
      return count <= MAX_GREEN;
    }
    if (element == "blue") {
      return count <= MAX_BLUE;
    }
  }

  return true;
}

bool under_max_counts(string cube_set) {
  istringstream input;
  input.str(cube_set);
  for (string color_count; getline(input, color_count, ',');) {
    if (!is_valid_cube_set(color_count)) {
      return false;
    }
  }

  return true;
}

string Day2::part1() {
  int sum = 0;

  string line;
  while ((line = nextline()) != "") {
    int game_id;

    // split on the colon to get "Game X", "...cubes"
    istringstream input;
    input.str(line);
    int i = 0;
    for (string element; getline(input, element, ':');) {
      trim(element);
      if (i == 0) {
        // for "Game XX", the game ID starts at the 5th position
        game_id = stoi(element.substr(5));
        i++;
        continue;
      }

      // split on semi-colon to get each presentation of cubes
      istringstream second_input;
      second_input.str(element);
      for (string cube_counts; getline(second_input, cube_counts, ';');) {
        if (!under_max_counts(cube_counts)) {
          goto nextline;
        }
      }

      sum += game_id;
    nextline:
      continue;
    }
  }
  return to_string(sum);
}

/*
As you continue your walk, the Elf poses a second question: in each game you
played, what is the fewest number of cubes of each color that could have been in
the bag to make the game possible?

Again consider the example games from earlier:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

    In game 1, the game could have been played with as few as 4 red, 2 green,
and 6 blue cubes. If any color had even one fewer cube, the game would have been
impossible. Game 2 could have been played with a minimum of 1 red, 3 green, and
4 blue cubes. Game 3 must have been played with at least 20 red, 13 green, and 6
blue cubes. Game 4 required at least 14 red, 3 green, and 15 blue cubes. Game 5
needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.

The power of a set of cubes is equal to the numbers of red, green, and blue
cubes multiplied together. The power of the minimum set of cubes in game 1
is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up these
five powers produces the sum 2286.

For each game, find the minimum set of cubes that must have been present. What
is the sum of the power of these sets?
*/

vector<int> get_counts(string cube_counts) {
  int reds = 0;
  int greens = 0;
  int blues = 0;

  // now split on spaces to get each color count pair
  istringstream input;
  input.str(cube_counts);
  for (string color_count; getline(input, color_count, ',');) {
    trim(color_count);

    int count;

    int i = 0;
    istringstream input;
    input.str(color_count);
    for (string element; getline(input, element, ' ');) {
      if (i == 0) {
        count = stoi(element);
        i++;
        continue;
      }

      if (element == "red") {
        reds = count;
      }
      if (element == "green") {
        greens = count;
      }
      if (element == "blue") {
        blues = count;
      }
    }
  }

  return vector<int>{reds, greens, blues};
}

string Day2::part2() {
  int sum = 0;

  for (string line; (line = nextline()) != "";) {
    int game_id;

    // split on the colon to get "Game X", "...cubes"
    istringstream input;
    input.str(line);
    int i = 0;
    for (string element; getline(input, element, ':');) {
      trim(element);

      if (i == 0) {
        // don't care about the Game ID this time
        i++;
        continue;
      }

      int reds = 0;
      int blues = 0;
      int greens = 0;

      // split on semi-colon to get each presentation of cubes
      istringstream second_input;
      second_input.str(element);
      for (string cube_counts; getline(second_input, cube_counts, ';');) {
        vector<int> counts = get_counts(cube_counts);

        reds = max(counts[0], reds);
        greens = max(counts[1], greens);
        blues = max(counts[2], blues);
      }

      sum += (reds * greens * blues);
    }
  }
  return to_string(sum);
}

/** Run the day's problems */
void Day2::run(int part) {
  cout << "Day " << thisDay;
  if (part == 1) {
    cout << " part 1: " << part1() << endl;
  } else {
    cout << " part 2: " << part2() << endl;
  };
}
