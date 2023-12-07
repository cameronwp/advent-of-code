import typing

def open_puzzle_input_and_loop(day: int):
    filepath = f"./data/day{day}.txt"
    with open(filepath, "r") as f:
        for line in f:
            yield line

