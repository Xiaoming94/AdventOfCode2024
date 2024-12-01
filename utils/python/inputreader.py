import sys

def read_input() -> str:
    input = ""
    for line in sys.stdin:
        input += line

    return input
