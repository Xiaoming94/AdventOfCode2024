from unittest import TestCase

import solution

class Day4Tests(TestCase):

    def test_problem1(self):
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

        result = solution.count_xmas(input)
        self.assertEqual(18, result)



