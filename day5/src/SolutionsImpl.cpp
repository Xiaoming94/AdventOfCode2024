#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Solution.h"

using Rules = std::unordered_map<uint32_t, std::vector<uint32_t>>;
using Prints_t = std::vector<uint32_t>;

namespace
{
  auto separateRuleFromInput(const std::string& input)
      -> std::pair<std::string, std::string>
  {
    const std::string delimiter = "\n\n";
    auto pos = input.find(delimiter);
    std::string rules;
    std::string updatePageNumbers;
    assert(pos != std::string::npos && "Invalid input string");
    if (pos != std::string::npos) {
      rules = input.substr(0, pos);
      updatePageNumbers =
          input.substr(pos + delimiter.length(), input.length());
    }
    return std::make_pair(rules, updatePageNumbers);
  }

  auto createOrderingRules(const std::string& orderingRuleStr) -> Rules
  {
    std::stringstream orderingRuleSS(orderingRuleStr);
    std::string line;
    std::unordered_map<uint32_t, std::vector<uint32_t>> rulesDict;
    while (std::getline(orderingRuleSS, line, '\n')) {
      const std::string delimiter = "|";
      auto pos = line.find(delimiter);
      assert(pos != std::string::npos && "Not in valid rule format");
      const auto pageBefore =
          static_cast<uint32_t>(std::stoi(line.substr(0, pos)));
      const auto pageAfter = static_cast<uint32_t>(
          std::stoi(line.substr(pos + delimiter.length(), line.length())));
      if (rulesDict.contains(pageBefore)) {
        rulesDict.at(pageBefore).push_back(pageAfter);
      } else {
        rulesDict.insert({pageBefore, {pageAfter}});
      }
    }
    return rulesDict;
  }

  void printPage(const Prints_t& print)
  {
    for (const auto num : print) {
      std::cout << num << " ";
    }
    std::cout << "\n";
  }
  bool isPrintValid(const Rules& rules, const Prints_t& print)
  {
    for (auto i = 0; i < print.size(); i++) {
      if (rules.contains(print[i])) {
        const auto pagesBefore = rules.at(print[i]);
        for (auto j = i; j >= 0; j--) {
          if (std::any_of(pagesBefore.begin(),
                          pagesBefore.end(),
                          [j, &print](const auto elem)
                          { return elem == print[j]; }))
          {
            return false;
          }
        }
      }
    }
    return true;
  }

  auto convertToPrintContainer(const std::string& printStr) -> Prints_t
  {
    std::stringstream printStream(printStr);
    std::string currentNumber;
    Prints_t pageVec;
    while (std::getline(printStream, currentNumber, ',')) {
      const auto currentNumberAsInt =
          static_cast<uint32_t>(std::stoi(currentNumber));
      pageVec.push_back(currentNumberAsInt);
    }

    return pageVec;
  }
}  // namespace

namespace solution
{

  auto sumMiddlePageNumbers(const std::string& input) -> uint32_t
  {
    const auto& [orderingRuleStr, linePrints] = separateRuleFromInput(input);
    const Rules rules = createOrderingRules(orderingRuleStr);
    Prints_t validPrints;

    std::stringstream lineStream(linePrints);
    std::string print;
    uint32_t sumMidPageNumbers {0U};
    while (std::getline(lineStream, print, '\n')) {
      const auto currentUpdatePrint = convertToPrintContainer(print);
      if (isPrintValid(rules, currentUpdatePrint)) {
        sumMidPageNumbers += currentUpdatePrint[currentUpdatePrint.size() / 2];
      }
    }
    return sumMidPageNumbers;
  }
}  // namespace solution
