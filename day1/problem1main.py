import sys

from solution import calc_distance
input = ""
for line in sys.stdin:
    input += line

print("The input is:")
print(input)

print(calc_distance.exec(input))
