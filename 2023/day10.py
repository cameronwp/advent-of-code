from collections import deque
import functools
import networkx as nx
import numpy as np
import sys
from typing import List, Set, Tuple


from utils import open_puzzle_input_and_loop

"""
The pipes are arranged in a two-dimensional grid of tiles:

    | is a vertical pipe connecting north and south.
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.

Based on the acoustics of the animal's scurrying, you're confident the pipe that contains the animal is one large, continuous loop.

For example, here is a square loop of pipe:

.....
.F-7.
.|.|.
.L-J.
.....

If the animal had entered this loop in the northwest corner, the sketch would instead look like this:

.....
.S-7.
.|.|.
.L-J.
.....

In the above diagram, the S tile is still a 90-degree F bend: you can tell because of how the adjacent pipes connect to it.

Unfortunately, there are also many pipes that aren't connected to the loop! This sketch shows the same loop as above:

-L|F7
7S-7|
L|7||
-L-J|
L|-JF

In the above diagram, you can still figure out which pipes form the main loop: they're the ones connected to S, pipes those pipes connect to, pipes those pipes connect to, and so on. Every pipe in the main loop connects to its two neighbors (including S, which will have exactly two pipes connecting to it, and which is assumed to connect back to those two pipes).

Here is a sketch that contains a slightly more complex main loop:

..F7.
.FJ|.
SJ.L7
|F--J
LJ...

Here's the same example sketch with the extra, non-main-loop pipe tiles also shown:

7-F7-
.FJ|7
SJLL7
|F--J
LJ.LJ

If you want to get out ahead of the animal, you should find the tile in the loop that is farthest from the starting position. Because the animal is in the pipe, it doesn't make sense to measure this by direct distance. Instead, you need to find the tile that would take the longest number of steps along the loop to reach from the starting point - regardless of which way around the loop the animal went.

In the first example with the square loop:

.....
.S-7.
.|.|.
.L-J.
.....

You can count the distance each tile in the loop is from the starting point like this:

.....
.012.
.1.3.
.234.
.....

In this example, the farthest point from the start is 4 steps away.

Here's the more complex loop again:

..F7.
.FJ|.
SJ.L7
|F--J
LJ...

Here are the distances for each tile on that loop:

..45.
.236.
01.78
14567
23...

Find the single giant loop starting at S. How many steps along the loop does it take to get from the starting position to the point farthest from the starting position?
"""


def find_start(puzzle_input):
    for r in range(len(puzzle_input)):
        for c in range(len(puzzle_input[r])):
            if puzzle_input[r][c] == "S":
                return r, c


def next_coords(puzzle_input, location, path=None) -> List[Tuple[int]] | None:
    r, c = location
    shape = puzzle_input[r][c]

    nexts = []
    if shape == "|":
        nexts = [(r - 1, c), (r + 1, c)]
    elif shape == "-":
        nexts = [(r, c - 1), (r, c + 1)]
    elif shape == "L":
        nexts = [(r - 1, c), (r, c + 1)]
    elif shape == "J":
        nexts = [(r - 1, c), (r, c - 1)]
    elif shape == "7":
        nexts = [(r, c - 1), (r + 1, c)]
    elif shape == "F":
        nexts = [(r + 1, c), (r, c + 1)]
    elif shape == ".":
        return None

    if path is None:
        return nexts

    if nexts[0] in path:
        return [nexts[1]]
    elif nexts[1] in path:
        return [nexts[0]]

    # print(location, shape)
    # print(nexts)
    # print(path)


def part1():
    # build an undirected graph
    # go out in both directions from S
    # stop when both iterators are on the same node
    puzzle_input = [line for line in open_puzzle_input_and_loop(day=10)]
    r_start, c_start = find_start(puzzle_input)

    print(f"Starting at {r_start, c_start}")

    starting_segments = []
    path = [(r_start, c_start)]

    for r in [-1, 0, 1]:
        for c in [-1, 0, 1]:
            if r == 0 and c == 0:
                continue

            res = next_coords(puzzle_input, (r_start + r, c_start + c))
            if res is None:
                continue
            [end1, end2] = res

            if puzzle_input[end1[0]][end1[1]] == "S":
                starting_segments.append(end2)
                path.append((r_start + r, c_start + c))
                # print(
                #     f"{(r_start + r, c_start + c)} '{puzzle_input[r_start+r][c_start+c]}'"
                # )
            elif puzzle_input[end2[0]][end2[1]] == "S":
                starting_segments.append(end1)
                path.append((r_start + r, c_start + c))
                # print(
                #     f"{(r_start + r, c_start + c)} '{puzzle_input[r_start+r][c_start+c]}'"
                # )

    iterator0_curr = starting_segments[0]
    iterator1_curr = starting_segments[1]
    iterator0_path = set([*path, *[starting_segments[0]]])
    iterator1_path = set([*path, *[starting_segments[1]]])

    steps = 2
    while iterator0_curr != iterator1_curr:
        # print(
        #     f"{iterator0_curr} '{puzzle_input[iterator0_curr[0]][iterator0_curr[1]]}'\t{iterator1_curr} '{puzzle_input[iterator1_curr[0]][iterator1_curr[1]]}'"
        # )
        [next_location0] = next_coords(puzzle_input, iterator0_curr, iterator0_path)
        iterator0_curr = next_location0
        iterator0_path.add(next_location0)

        [next_location1] = next_coords(puzzle_input, iterator1_curr, iterator1_path)
        iterator1_curr = next_location1
        iterator1_path.add(next_location1)

        steps += 1

    return steps


"""

"""


def part2():
    for line in open_puzzle_input_and_loop(day=10):
        pass


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
