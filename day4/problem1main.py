import sys

import solution
sys.path.insert(1, "../utils/python/")

from inputreader import read_input
input = read_input()

print("The input is:")
print(input)

print(solution.count_xmas(input))

