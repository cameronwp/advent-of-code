#include "day5.hpp"
#include "lib/split_and_loop.cpp"
#include "lib/trim.cpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <limits.h>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/*
seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4

The almanac starts by listing which seeds need to be planted: seeds 79, 14, 55,
and 13.

The rest of the almanac contains a list of maps which describe how to convert
numbers from a source category into numbers in a destination category. That is,
the section that starts with seed-to-soil map: describes how to convert a seed
number (the source) to a soil number (the destination). This lets the gardener
and his team know which soil to use with which seeds, which water to use with
which fertilizer, and so on.

Rather than list every source number and its corresponding destination number
one by one, the maps describe entire ranges of numbers that can be converted.
Each line within a map contains three numbers: the destination range start, the
source range start, and the range length.

Consider again the example seed-to-soil map:

50 98 2
52 50 48

The first line has a destination range start of 50, a source range start of 98,
and a range length of 2. This line means that the source range starts at 98 and
contains two values: 98 and 99. The destination range is the same length, but it
starts at 50, so its two values are 50 and 51. With this information, you know
that seed number 98 corresponds to soil number 50 and that seed number 99
corresponds to soil number 51.

The second line means that the source range starts at 50 and contains 48 values:
50, 51, ..., 96, 97. This corresponds to a destination range starting at 52 and
also containing 48 values: 52, 53, ..., 98, 99. So, seed number 53 corresponds
to soil number 55.

Any source numbers that aren't mapped correspond to the same destination number.
So, seed number 10 corresponds to soil number 10.

So, the entire list of seed numbers and their corresponding soil numbers looks
like this:

seed  soil
0     0
1     1
...   ...
48    48
49    49
50    52
51    53
...   ...
96    98
97    99
98    50
99    51

With this map, you can look up the soil number required for each initial seed
number:

    Seed number 79 corresponds to soil number 81.
    Seed number 14 corresponds to soil number 14.
    Seed number 55 corresponds to soil number 57.
    Seed number 13 corresponds to soil number 13.

The gardener and his team want to get started as soon as possible, so they'd
like to know the closest location that needs a seed. Using these maps, find the
lowest location number that corresponds to any of the initial seeds. To do this,
you'll need to convert each seed number through other categories until you can
find its corresponding location number. In this example, the corresponding types
are:

    Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78,
humidity 78, location 82. Seed 14, soil 14, fertilizer 53, water 49, light 42,
temperature 42, humidity 43, location 43. Seed 55, soil 57, fertilizer 57, water
53, light 46, temperature 82, humidity 82, location 86. Seed 13, soil 13,
fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.

So, the lowest location number in this example is 35.

What is the lowest location number that corresponds to any of the initial seed
numbers?
*/

string Day5::part1() {
  // a matrix where column is the stage of the run, e.g. seed-to-soil, and each
  // row is a seed. as the run progresses, seeds move left to right. not
  // guaranteed that the index of each seed remains the same throughout the run
  vector<vector<long long int>> seed_tracker{vector<long long int>{}};

  // which map we're on
  int map_pos = 0;
  bool have_seeds = false;
  for (string line; (line = nextline()) != uninitialized;) {
    cout << line << endl;

    if (!have_seeds) {
      // capture the seeds and put them in their starting position
      split_and_loop(line.substr(7), ' ', [&](string num, int _i) {
        trim(num);
        long long int n = stoll(num);
        seed_tracker[0].push_back(n);
      });

      have_seeds = true;
      continue;
    }

    if (line == "") {
      continue;
    }

    if (int(line[0]) > 57) {
      map_pos++;
      int num_seeds = seed_tracker[map_pos - 1].size();
      long long int sizel = num_seeds;
      seed_tracker.push_back(vector<long long int>(sizel));
      seed_tracker[map_pos] = seed_tracker[map_pos - 1];
      continue;
    }

    long long int destination_range_start, source_range_start, range_length;

    split_and_loop(line, ' ', [&](string num, int j) {
      trim(num);

      if (j == 0) {
        destination_range_start = stoll(num);
      } else if (j == 1) {
        source_range_start = stoll(num);
      } else if (j == 2) {
        range_length = stoll(num);
      }
    });

    long long int source_range_end = source_range_start + range_length;

    vector<long long int> &last_round = seed_tracker[map_pos - 1];
    vector<long long int> &this_round = seed_tracker[map_pos];

    for (int k = 0; k < this_round.size(); k++) {
      long long int seed = last_round.at(k);
      bool seed_in_source_range =
          seed >= source_range_start && seed < source_range_end;
      if (seed_in_source_range) {
        long long int destination =
            destination_range_start + (seed - source_range_start);
        this_round.at(k) = destination;
      }
    }
  }

  long long int min_location = numeric_limits<long long int>::max();

  for (auto &loc : seed_tracker.back()) {
    min_location = min(min_location, loc);
  }

  return to_string(min_location);
}

/*

 */

string Day5::part2() {
  for (string line; (line = nextline()) != "";) {
    //
  }

  return "";
}

/** Run the day's problems */
void Day5::run(int part) {
  cout << "Day " << thisDay;
  if (part == 1) {
    cout << " part 1: " << part1() << endl;
  } else {
    cout << " part 2: " << part2() << endl;
  };
}
