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
After examining the maps a bit longer, your attention is drawn to a curious fact: the number of nodes with names ending in A is equal to the number ending in Z! If you were a ghost, you'd probably just start at every node that ends with A and follow all of the paths at the same time until they all simultaneously end up at nodes that end with Z.

For example:

LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)

Here, there are two starting nodes, 11A and 22A (because they both end with A). As you follow each left/right instruction, use that instruction to simultaneously navigate away from both nodes you're currently on. Repeat this process until all of the nodes you're currently on end with Z. (If only some of the nodes you're on end with Z, they act like any other node and you continue as normal.) In this example, you would proceed as follows:

    Step 0: You are at 11A and 22A.
    Step 1: You choose all of the left paths, leading you to 11B and 22B.
    Step 2: You choose all of the right paths, leading you to 11Z and 22C.
    Step 3: You choose all of the left paths, leading you to 11B and 22Z.
    Step 4: You choose all of the right paths, leading you to 11Z and 22B.
    Step 5: You choose all of the left paths, leading you to 11B and 22C.
    Step 6: You choose all of the right paths, leading you to 11Z and 22Z.

So, in this example, you end up entirely on nodes that end in Z after 6 steps.

Simultaneously start on every node that ends with A. How many steps does it take before you're only on nodes that end with Z?
"""


def part2():
    G = nx.DiGraph()

    starts = []
    all_num_steps = []
    steps = []
    for line in open_puzzle_input_and_loop(day=8):
        if len(steps) == 0:
            steps = [c for c in line if c != "\n"]
            continue

        if line in ["", "\n"]:
            continue

        node = line[:3]
        left = line[7:10]
        right = line[12:15]

        if left != right:
            G.add_edge(node, left, dir="L")
            G.add_edge(node, right, dir="R")
        else:
            G.add_edge(node, left, dir="*")

        if node[2] == "A":
            starts.append(node)

    for s in range(len(starts)):
        num_steps = 0
        curr = starts[s]
        for dir in gen_dir(steps):
            num_steps += 1
            out_edges = [edge for edge in G.out_edges(curr, data=True)]
            curr = [
                out_edge
                for _curr, out_edge, data in out_edges
                if data["dir"] in [dir, "*"]
            ][0]
            if curr[2] == "Z":
                break
        all_num_steps.append(num_steps)

    return np.lcm.reduce(all_num_steps)


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
