import functools
import networkx as nx
import numpy as np
import sys
from typing import List

from utils import open_puzzle_input_and_loop

"""

"""


def part1():
    for line in open_puzzle_input_and_loop(day=10):
        pass


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
