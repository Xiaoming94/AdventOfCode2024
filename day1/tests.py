import unittest

from . import solution
class Day1Tests(unittest.TestCase):
    def test_problem1(self):

        input = ("3  4\n"
                 "4  3\n"
                 "2  5\n"
                 "1  3\n"
                 "3  9\n"
                 "3  3")

        result = solution.calc_distance(input)
        self.assertEqual(result, 11)
