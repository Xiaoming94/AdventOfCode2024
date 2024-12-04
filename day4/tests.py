from unittest import TestCase

import solution

class Day4Tests(TestCase):

    input = ("MMMSXXMASM\n"
             "MSAMXMSMSA\n"
             "AMXSXMAAMM\n"
             "MSAMASMSMX\n"
             "XMASAMXAMM\n"
             "XXAMMXXAMA\n"
             "SMSMSASXSS\n"
             "SAXAMASAAA\n"
             "MAMMMXMMMM\n"
             "MXMXAXMASX")

    def test_problem1(self):
        result = solution.count_xmas(self.input)
        self.assertEqual(18, result)

    def test_problem2(self):
        result = solution.count_cross_mas(self.input)
        self.assertEqual(9, result)

