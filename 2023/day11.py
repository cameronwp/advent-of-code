from collections import deque
import functools
import networkx as nx
import numpy as np
from scipy.spatial.distance import cityblock
import sys
from typing import List, Set, Tuple


from utils import open_puzzle_input_and_loop

"""
The researcher has collected a bunch of data and compiled the data into a single giant image (your puzzle input). The image includes empty space (.) and galaxies (#). For example:

...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....

The researcher is trying to figure out the sum of the lengths of the shortest path between every pair of galaxies. However, there's a catch: the universe expanded in the time it took the light from those galaxies to reach the observatory.

Due to something involving gravitational effects, only some space expands. In fact, the result is that any rows or columns that contain no galaxies should all actually be twice as big.

In the above example, three columns and two rows contain no galaxies:

   v  v  v
 ...#......
 .......#..
 #.........
>..........<
 ......#...
 .#........
 .........#
>..........<
 .......#..
 #...#.....
   ^  ^  ^

These rows and columns need to be twice as big; the result of cosmic expansion therefore looks like this:

....#........
.........#...
#............
.............
.............
........#....
.#...........
............#
.............
.............
.........#...
#....#.......

Equipped with this expanded universe, the shortest path between every pair of galaxies can be found. It can help to assign every galaxy a unique number:

....1........
.........2...
3............
.............
.............
........4....
.5...........
............6
.............
.............
.........7...
8....9.......

In these 9 galaxies, there are 36 pairs. Only count each pair once; order within the pair doesn't matter. For each pair, find any shortest path between the two galaxies using only steps that move up, down, left, or right exactly one . or # at a time. (The shortest path between two galaxies is allowed to pass through another galaxy.)

For example, here is one of the shortest paths between galaxies 5 and 9:

....1........
.........2...
3............
.............
.............
........4....
.5...........
.##.........6
..##.........
...##........
....##...7...
8....9.......

This path has length 9 because it takes a minimum of nine steps to get from galaxy 5 to galaxy 9 (the eight locations marked # plus the step onto galaxy 9 itself). Here are some other example shortest path lengths:

    Between galaxy 1 and galaxy 7: 15
    Between galaxy 3 and galaxy 6: 17
    Between galaxy 8 and galaxy 9: 5

In this example, after expanding the universe, the sum of the shortest path between all 36 pairs of galaxies is 374.

Expand the universe, then find the length of the shortest path between every pair of galaxies. What is the sum of these lengths?
"""


def part1():
    puzzle_input = [
        [0 if char == "." else 1 for char in line if char != "\n"]
        for line in open_puzzle_input_and_loop(day=11)
    ]

    row_first = np.array(puzzle_input, dtype=np.int8)
    num_cols = len(puzzle_input[0])

    empty_rows = []
    empty_cols = []

    for r in range(len(row_first)):
        empty = all([pos == 0 for pos in row_first[r]])
        if empty:
            empty_rows.append(r)

    for r in reversed(empty_rows):
        row_first = np.insert(row_first, r, np.zeros(num_cols), axis=0)

    # get an accurate count of the number of rows after adding expanded rows
    num_rows = len(row_first)

    col_first = row_first.T

    for c in range(len(col_first)):
        empty = all([pos == 0 for pos in col_first[c]])
        if empty:
            empty_cols.append(c)

    for c in reversed(empty_cols):
        col_first = np.insert(col_first, c, np.zeros(num_rows), axis=0)

    expanded_galaxy_map = col_first.T
    galaxy_rows, galaxy_cols = np.nonzero(expanded_galaxy_map)

    all_distances = 0
    for i in range(len(galaxy_rows)):
        for j in reversed(range(len(galaxy_rows))):
            if i > j:
                break

            all_distances += cityblock(
                np.array([galaxy_rows[i], galaxy_cols[i]]),
                np.array([galaxy_rows[j], galaxy_cols[j]]),
            )

    return all_distances


"""
Now, instead of the expansion you did before, make each empty row or column one million times larger. That is, each empty row should be replaced with 1000000 empty rows, and each empty column should be replaced with 1000000 empty columns.

(In the example above, if each empty row or column were merely 10 times larger, the sum of the shortest paths between every pair of galaxies would be 1030. If each empty row or column were merely 100 times larger, the sum of the shortest paths between every pair of galaxies would be 8410. However, your universe will need to expand far beyond these values.)

Starting with the same initial image, expand the universe according to these new rules, then find the length of the shortest path between every pair of galaxies. What is the sum of these lengths?
"""


def part2():
    puzzle_input = [
        [0 if char == "." else 1 for char in line if char != "\n"]
        for line in open_puzzle_input_and_loop(day=11)
    ]

    row_first = np.array(puzzle_input, dtype=np.int8)
    galaxy_rows, galaxy_cols = np.nonzero(row_first)

    empty_rows = []
    empty_cols = []

    for r in range(len(row_first)):
        empty = all([pos == 0 for pos in row_first[r]])
        if empty:
            empty_rows.append(r)

    col_first = row_first.T

    for c in range(len(col_first)):
        empty = all([pos == 0 for pos in col_first[c]])
        if empty:
            empty_cols.append(c)

    for ri in reversed(empty_rows):
        for rj in reversed(range(len(galaxy_rows))):
            if galaxy_rows[rj] > ri:
                galaxy_rows[rj] += 1e6 - 1

    for ci in reversed(empty_cols):
        for cj in reversed(range(len(galaxy_cols))):
            if galaxy_cols[cj] > ci:
                galaxy_cols[cj] += 1e6 - 1

    all_distances = 0
    for i in range(len(galaxy_rows)):
        for j in reversed(range(len(galaxy_rows))):
            if i > j:
                break

            all_distances += cityblock(
                np.array([galaxy_rows[i], galaxy_cols[i]]),
                np.array([galaxy_rows[j], galaxy_cols[j]]),
            )

    return all_distances


if __name__ == "__main__":
    part = None

    if len(sys.argv) >= 2:
        part = sys.argv[1]

    if part == "1":
        print(part1())
    elif part == "2":
        print(part2())
    else:
        print("Usage: 'python dayX.py PART', where PART is '1' or '2'")
