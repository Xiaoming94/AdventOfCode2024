#include <iostream>
#include <string>

#include "Solution.h"

int main()
{
  std::string line;
  std::string input;
  while (std::getline(std::cin, line)) {
    input += line + "\n";
  }

  std::cout << "Current Puzzle Input:\n" << input << std::endl;
  std::cout << "Problem1 solution: " << solution::sumMiddlePageNumbers(input)
            << std::endl;

  std::cout << "Problem2 solution: "
            << solution::fixBadPageSumMiddleNumbers(input) << std::endl;
}
