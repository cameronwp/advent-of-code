import functools
import numpy as np
import sys
import typing

from utils import open_puzzle_input_and_loop

"""
In Camel Cards, you get a list of hands, and your goal is to order them based on the strength of each hand. A hand consists of five cards labeled one of A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2. The relative strength of each card follows this order, where A is the highest and 2 is the lowest.

Every hand is exactly one type. From strongest to weakest, they are:

    Five of a kind, where all five cards have the same label: AAAAA
    Four of a kind, where four cards have the same label and one card has a different label: AA8AA
    Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
    Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
    Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
    One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
    High card, where all cards' labels are distinct: 23456

Hands are primarily ordered based on type; for example, every full house is stronger than any three of a kind.

If two hands have the same type, a second ordering rule takes effect. Start by comparing the first card in each hand. If these cards are different, the hand with the stronger first card is considered stronger. If the first card in each hand have the same label, however, then move on to considering the second card in each hand. If they differ, the hand with the higher second card wins; otherwise, continue with the third card in each hand, then the fourth, then the fifth.

So, 33332 and 2AAAA are both four of a kind hands, but 33332 is stronger because its first card is stronger. Similarly, 77888 and 77788 are both a full house, but 77888 is stronger because its third card is stronger (and both hands have the same first and second card).

To play Camel Cards, you are given a list of hands and their corresponding bid (your puzzle input). For example:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483

This example shows five hands; each hand is followed by its bid amount. Each hand wins an amount equal to its bid multiplied by its rank, where the weakest hand gets rank 1, the second-weakest hand gets rank 2, and so on up to the strongest hand. Because there are five hands in this example, the strongest hand will have rank 5 and its bid will be multiplied by 5.

So, the first step is to put the hands in order of strength:

    32T3K is the only one pair and the other hands are all a stronger type, so it gets rank 1.
    KK677 and KTJJT are both two pair. Their first cards both have the same label, but the second card of KK677 is stronger (K vs T), so KTJJT gets rank 2 and KK677 gets rank 3.
    T55J5 and QQQJA are both three of a kind. QQQJA has a stronger first card, so it gets rank 5 and T55J5 gets rank 4.

Now, you can determine the total winnings of this set of hands by adding up the result of multiplying each hand's bid with its rank (765 * 1 + 220 * 2 + 28 * 3 + 684 * 4 + 483 * 5). So the total winnings in this example are 6440.

Find the rank of every hand in your set. What are the total winnings?
"""

CARD_RANKS = ["2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"]


class Hand:
    def __init__(self, cards):
        self.cards = cards
        self._score = -1

    def __str__(self):
        return f"{self.cards} ({self.score()})"

    def __repr__(self):
        return str(self)

    def __lt__(self, other):
        my_score = self.score()
        other_score = other.score()

        if my_score != other_score:
            return my_score < other_score

        for i in range(5):
            my_card_rank = CARD_RANKS.index(self.cards[i])
            other_card_rank = CARD_RANKS.index(other.cards[i])
            if my_card_rank != other_card_rank:
                return my_card_rank < other_card_rank

        # the hands are apparently identical
        return False

    def score(self):
        """
        Returns a 6 bit number to represent the hand's score
        111111
        ^ 5 of a kind
         ^ 4 of a kind
          ^ 3 of a kind
           ^ 2 pair
            ^ 1 pair
             ^ high card

        A full house will have both 3 of a kind and 1 pair.
        2 pair will have both 2 pair and 1 pair
        """
        if self._score != -1:
            return self._score

        # start with a high card hand
        score = 1

        hits = {card: 0 for card in set(self.cards)}
        for card in self.cards:
            hits[card] += 1

        num_pairs = 0
        for card in hits:
            if hits[card] == 5:
                score = score | 2**5
            if hits[card] == 4:
                score = score | 2**4
            if hits[card] == 3:
                score = score | 2**3
            if hits[card] == 2:
                num_pairs += 1
                if num_pairs == 1:
                    score = score | 2**1
                elif num_pairs == 2:
                    score = score | 2**2

        self._score = score
        return score


def part1():
    puzzle_input = []
    for line in open_puzzle_input_and_loop(day=7):
        cards, bid = line.split()
        puzzle_input.append({"cards": Hand(cards), "bid": int(bid)})

    ranked_puzzle_input = sorted(puzzle_input, key=lambda o : o["cards"])
    return sum([wager["bid"] * (i + 1) for i, wager in enumerate(ranked_puzzle_input)])

"""
Instructions here
"""


def part2():
    for line in open_puzzle_input_and_loop(day=7):
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
