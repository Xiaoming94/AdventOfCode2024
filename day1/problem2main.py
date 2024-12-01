import sys

from solution import calc_simularity
sys.path.insert(1, "../utils/python/")

from inputreader import read_input
input = read_input()

print("The input is:")
print(input)

print(calc_simularity.exec(input))
