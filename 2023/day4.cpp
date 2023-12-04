#include "day4.hpp"
#include "lib/split_and_loop.cpp"
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
The Elf leads you over to the pile of colorful cards. There, you discover dozens
of scratchcards, all with their opaque covering already scratched off. Picking
one up, it looks like each card has two lists of numbers separated by a vertical
bar (|): a list of winning numbers and then a list of numbers you have. You
organize the information into a table (your puzzle input).

As far as the Elf has been able to figure out, you have to figure out which of
the numbers you have appear in the list of winning numbers. The first match
makes the card worth one point and each match after the first doubles the point
value of that card.

For example:

Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11

In the above example, card 1 has five winning numbers (41, 48, 83, 86, and 17)
and eight numbers you have (83, 86, 6, 31, 17, 9, 48, and 53). Of the numbers
you have, four of them (48, 83, 17, and 86) are winning numbers! That means card
1 is worth 8 points (1 for the first match, then doubled three times for each of
the three matches after the first).

    Card 2 has two winning numbers (32 and 61), so it is worth 2 points.
    Card 3 has two winning numbers (1 and 21), so it is worth 2 points.
    Card 4 has one winning number (84), so it is worth 1 point.
    Card 5 has no winning numbers, so it is worth no points.
    Card 6 has no winning numbers, so it is worth no points.

So, in this example, the Elf's pile of scratchcards is worth 13 points.

Take a seat in the large pile of colorful cards. How many points are they worth
in total?
*/

string Day4::part1() {
  int sum = 0;

  for (string line; (line = nextline()) != "";) {
    split_and_loop(line, ':', [&sum, &line](string element) {
      // we're looking at the "Card X" part of the line
      if (element[0] == 'C') {
        return;
      }

      set<int> winning_numbers;

      // winning numbers | our numbers
      int i = 0;
      int point_value = 0;
      split_and_loop(element, '|', [&](string card) {
        trim(card);

        // split on spaces, turn into ints
        // we'll run this for the winning numbers first, then our numbers
        split_and_loop(card, ' ', [&](string num) {
          trim(num);

          if (num == "") {
            return;
          }

          if (i == 0) {
            winning_numbers.insert(stoi(num));
            return;
          }

          if (winning_numbers.find(stoi(num)) != winning_numbers.end()) {
            if (point_value == 0) {
              point_value = 1;
            } else {
              point_value *= 2;
            }
          }
        });

        i++;
      });

      sum += point_value;
    });
  }

  return to_string(sum);
}

/*

*/

string Day4::part2() {
  for (string line; (line = nextline()) != "";) {
    //
  }

  return "";
}

/** Run the day's problems */
void Day4::run(int part) {
  cout << "Day " << thisDay;
  if (part == 1) {
    cout << " part 1: " << part1() << endl;
  } else {
    cout << " part 2: " << part2() << endl;
  };
}
