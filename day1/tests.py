import unittest

from solution import calc_distance
class Day1Tests(unittest.TestCase):
    input = ("3  4\n"
             "4  3\n"
             "2  5\n"
             "1  3\n"
             "3  9\n"
             "3  3")
    def test_problem1(self):

        result = calc_distance.exec(self.input)
        self.assertEqual(result, 11)
