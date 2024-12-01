import sys

from solution import calc_distance
sys.path.insert(1, "../utils/python/")

from inputreader import read_input
input = read_input()

print("The input is:")
print(input)

print(calc_distance.exec(input))
