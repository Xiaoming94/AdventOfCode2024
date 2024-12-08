#include <gtest/gtest.h>

#include "solution.h"

constexpr auto INPUT =
    "............\n"
    "........0...\n"
    ".....0......\n"
    ".......0....\n"
    "....0.......\n"
    "......A.....\n"
    "............\n"
    "............\n"
    "........A...\n"
    ".........A..\n"
    "............\n"
    "............";

TEST(AoCDay8Test, verifyProblem1Solution)
{
  const auto results = solution::solveProblem1(INPUT);
  ASSERT_EQ(14u, results);
}
