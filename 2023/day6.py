import functools
import numpy as np
import sys
import typing

from utils import open_puzzle_input_and_loop

"""
As part of signing up, you get a sheet of paper (your puzzle input) that lists the time allowed for each race and also the best distance ever recorded in that race. To guarantee you win the grand prize, you need to make sure you go farther in each race than the current record holder.

The organizer brings you over to the area where the boat races are held. The boats are much smaller than you expected - they're actually toy boats, each with a big button on top. Holding down the button charges the boat, and releasing the button allows the boat to move. Boats move faster if their button was held longer, but time spent holding the button counts against the total race time. You can only hold the button at the start of the race, and boats don't move until the button is released.

For example:

Time:      7  15   30
Distance:  9  40  200

This document describes three races:

    The first race lasts 7 milliseconds. The record distance in this race is 9 millimeters.
    The second race lasts 15 milliseconds. The record distance in this race is 40 millimeters.
    The third race lasts 30 milliseconds. The record distance in this race is 200 millimeters.

Your toy boat has a starting speed of zero millimeters per millisecond. For each whole millisecond you spend at the beginning of the race holding down the button, the boat's speed increases by one millimeter per millisecond.

So, because the first race lasts 7 milliseconds, you only have a few options:

    Don't hold the button at all (that is, hold it for 0 milliseconds) at the start of the race. The boat won't move; it will have traveled 0 millimeters by the end of the race.
    Hold the button for 1 millisecond at the start of the race. Then, the boat will travel at a speed of 1 millimeter per millisecond for 6 milliseconds, reaching a total distance traveled of 6 millimeters.
    Hold the button for 2 milliseconds, giving the boat a speed of 2 millimeters per millisecond. It will then get 5 milliseconds to move, reaching a total distance of 10 millimeters.
    Hold the button for 3 milliseconds. After its remaining 4 milliseconds of travel time, the boat will have gone 12 millimeters.
    Hold the button for 4 milliseconds. After its remaining 3 milliseconds of travel time, the boat will have gone 12 millimeters.
    Hold the button for 5 milliseconds, causing the boat to travel a total of 10 millimeters.
    Hold the button for 6 milliseconds, causing the boat to travel a total of 6 millimeters.
    Hold the button for 7 milliseconds. That's the entire duration of the race. You never let go of the button. The boat can't move until you let go of the button. Please make sure you let go of the button so the boat gets to move. 0 millimeters.

Since the current record for this race is 9 millimeters, there are actually 4 different ways you could win: you could hold the button for 2, 3, 4, or 5 milliseconds at the start of the race.

In the second race, you could hold the button for at least 4 milliseconds and at most 11 milliseconds and beat the record, a total of 8 different ways to win.

In the third race, you could hold the button for at least 11 milliseconds and no more than 19 milliseconds and still beat the record, a total of 9 ways you could win.

To see how much margin of error you have, determine the number of ways you can beat the record in each race; in this example, if you multiply these values together, you get 288 (4 * 8 * 9).

Determine the number of ways you could beat the record in each race. What do you get if you multiply these numbers together?
"""

# distance = speed * time_travel
# time_total = time_held + time_travel
# speed = time_hold

# speed range * time range in (distance, infty]
# [0, time_hold] * [time_total - time_hold, time_total] in (distance, infty]
# solve for time_hold

# [
#   min(0, 0, (time_total - time_hold) * time_hold, time_hold * time_total),
#   max(0, 0, (time_total - time_hold) * time_hold, time_hold * time_total)
# ] in (distance, infty]
# [
#   min(0, (time_total - time_hold) * time_hold, time_hold * time_total),
#   max((time_total - time_hold) * time_hold, time_hold * time_total)
# ] in (distance, infty]
# [
#   min(0, (time_total - time_hold) * time_hold, time_hold * time_total),
#   max((time_total - time_hold) * time_hold, time_hold * time_total)
# ] = (distance, infty]
# [
#   min(0, (time_total - time_hold) * time_hold, time_hold * time_total),
#   max((time_total - time_hold) * time_hold, time_hold * time_total)
# ] > (distance, distance]
# [
#   min(0, (time_total - time_hold) * time_hold, time_hold * time_total) - distance,
#   max((time_total - time_hold) * time_hold, time_hold * time_total) - distance
# ] > [0, 0]
#
# min((time_total - time_hold) * time_hold, time_hold * time_total) - distance > 0
# max((time_total - time_hold) * time_hold, time_hold * time_total) - distance > 0

# (time_total - time_hold) * time_hold - distance > 0
# time_total * time_hold - time_hold^2 - distance > 0
# let time_hold = x, A = - 1, time_total = B, distance = C
# Ax^2 + BX + C = 0
# (-B +/- sqrt(1 - 4*-1*C)) / -2
# (-B +/- sqrt(1 + 4*C)) / -2
# x = (-B + sqrt(1 + 4C)) / -2, (-B - sqrt(1 + 4C)) / -2
# x = (-B + sqrt(1 + 4C)) / -2, (B + sqrt(1 + 4C)) / 2

# time_hold = (-time_total + sqrt(1 + 4 * distance)) / -2 or
#             (time_total + sqrt(1 + 4 * distance)) / 2
# plug in to get lower bound and upper bound

# example
# time_hold = (-7 + sqrt(1 + 4 * 9)) / -2, (7 + sqrt(1 + 4 * 9)) / 2
#           = 1.7, 5.3
# whole numbers = 2, 5
#

# round whole numbers. remember distance needs to be greater, so the lower bound should be floor(n + 1)

def quadratic_equation(a: int, b: int, c: int):
    return (
        (b * -1 + np.sqrt(b**2 + 4 * a * c)) / (2 * a),
        (b * -1 - np.sqrt(b**2 + 4 * a * c)) / (2 * a))

def part1():
    i = 0

    races = []

    for line in open_puzzle_input_and_loop(day=6):
        elements = line.split()
        if i == 0:
            races = [{"time_total": int(time), "distance": None} for time in elements[1:]]
        else:
            for j, distance in enumerate(elements[1:]):
                races[j]["distance"] = int(distance)
        i += 1

    ways = []
    for race in races:
        lower, upper = quadratic_equation(-1, race["time_total"], race["distance"])
        number_of_ways_to_beat_record = np.floor(upper) - np.floor(lower + 1) + 1
        ways.append(number_of_ways_to_beat_record)

    return functools.reduce(lambda x, y : x * y, ways, 1)


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
