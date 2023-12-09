import functools
import networkx as nx
import numpy as np
import sys
from typing import List

from utils import open_puzzle_input_and_loop

"""
After examining the maps for a bit, two nodes stick out: AAA and ZZZ. You feel like AAA is where you are now, and you have to follow the left/right instructions until you reach ZZZ.

This format defines each node of the network individually. For example:

RL

AAA = (BBB, CCC)
BBB = (DDD, EEE)
CCC = (ZZZ, GGG)
DDD = (DDD, DDD)
EEE = (EEE, EEE)
GGG = (GGG, GGG)
ZZZ = (ZZZ, ZZZ)

Starting with AAA, you need to look up the next element based on the next left/right instruction in your input. In this example, start with AAA and go right (R) by choosing the right element of AAA, CCC. Then, L means to choose the left element of CCC, ZZZ. By following the left/right instructions, you reach ZZZ in 2 steps.

Of course, you might not find ZZZ right away. If you run out of left/right instructions, repeat the whole sequence of instructions as necessary: RL really means RLRLRLRLRLRLRLRL... and so on. For example, here is a situation that takes 6 steps to reach ZZZ:

LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ)

Starting at AAA, follow the left/right instructions. How many steps are required to reach ZZZ?
"""


def gen_dir(steps: List[str]):
    i = 0
    num_steps = len(steps)
    while True:
        j = i % num_steps
        yield steps[j]
        i += 1


def part1():
    G = nx.DiGraph()

    start = "AAA"
    goal = "ZZZ"

    steps = []
    for line in open_puzzle_input_and_loop(day=8):
        if len(steps) == 0:
            steps = [c for c in line if c != "\n"]
            continue

        if line == "":
            continue

        node = line[:3]
        left = line[7:10]
        right = line[12:15]

        if left != right:
            G.add_edge(node, left, dir="L")
            G.add_edge(node, right, dir="R")
        else:
            G.add_edge(node, left, dir="*")

    num_steps = 0
    curr = start
    for dir in gen_dir(steps):
        num_steps += 1
        out_edges = [edge for edge in G.out_edges(curr, data=True)]
        curr = [
            out_edge for _curr, out_edge, data in out_edges if data["dir"] in [dir, "*"]
        ][0]
        if curr == goal:
            break

    return num_steps


"""
instructions
"""


def part2():
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
