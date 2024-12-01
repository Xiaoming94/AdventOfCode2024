import sys

from solution import calc_simularity
input = ""
for line in sys.stdin:
    input += line

print("The input is:")
print(input)

print(calc_simularity.exec(input))
