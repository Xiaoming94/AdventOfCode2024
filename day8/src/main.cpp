#include <iostream>
#include <sstream>

#include "solution.h"

int main()
{
  std::string line;
  std::stringstream inputSs;
  while (std::getline(std::cin, line, '\n')) {
    inputSs << line << "\n";
  }

  const auto input = inputSs.str();
  const auto resultsProblem1 = solution::solveProblem1(input);
  std::cout << "Problem input is:\n" << input;
  std::cout << "problem 1 solution: " << resultsProblem1 << std::endl;
}
