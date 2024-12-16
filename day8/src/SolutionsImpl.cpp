#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "solution.h"

namespace
{
  struct Pos
  {
    int32_t xPos;
    int32_t yPos;

    inline auto operator==(const Pos& other) const -> bool
    {
      return xPos == other.xPos && yPos == other.yPos;
    }

    inline auto operator+(const Pos& other) const -> Pos
    {
      return Pos {.xPos = (this->xPos + other.xPos),
                  .yPos = (this->yPos + other.xPos)};
    }

    inline auto operator-(const Pos& other) const -> Pos
    {
      return Pos {.xPos = (this->xPos - other.xPos),
                  .yPos = (this->yPos - other.yPos)};
    }
  };

  class BoundChecker
  {
  public:
    BoundChecker(uint32_t width, uint32_t height)
        : m_width(width)
        , m_height(height)
    {
    }

    auto withinBounds(const Pos& pos) const -> bool
    {
      const auto& [xPos, yPos] = pos;
      return (xPos >= 0 and yPos >= 0) and (xPos < m_width and yPos < m_height);
    }

  private:
    const uint32_t m_width;
    const uint32_t m_height;
  };
}  // namespace

using Positions_t = std::vector<Pos>;
using AntennaPositions_t = std::unordered_map<char, Positions_t>;
using Line_t = std::vector<Pos>;

namespace
{
  auto createSolutionModel(const std::string& input)
      -> std::pair<BoundChecker, AntennaPositions_t>
  {
    auto verticalBound = 0;
    int32_t horizontalPos;
    std::stringstream sstreamOf(input);
    std::string line;
    AntennaPositions_t antennaPosData;
    while (std::getline(sstreamOf, line, '\n')) {
      horizontalPos = 0;
      for (const auto& ch : line) {
        if (ch != '.') {
          const auto currentPos =
              Pos {.xPos = horizontalPos, .yPos = verticalBound};
          antennaPosData[ch].push_back(currentPos);
        }
        horizontalPos += 1;
      }
      verticalBound += 1;
    }

    const BoundChecker boundChecker(horizontalPos, verticalBound);
    return std::make_pair(boundChecker, antennaPosData);
  }

  auto calcDistance(const Pos& pos1, const Pos& pos2) -> Pos
  {
    const auto& [x1, y1] = pos1;
    const auto& [x2, y2] = pos2;

    const auto xDistance = x1 - x2;
    const auto yDistance = y1 - y2;

    return Pos {
        .xPos = xDistance,
        .yPos = yDistance,
    };
  }

  auto findGCD(const int32_t lastReminder, const int32_t currentVal) -> int32_t
  {
    if (lastReminder > currentVal) {
      return findGCD(currentVal, lastReminder);
    } else if (lastReminder == 0) {
      return currentVal;
    } else {
      return findGCD(currentVal % lastReminder, lastReminder);
    }
  }

  auto gradientOf(const Pos& pos) -> Pos
  {
    const auto& [x, y] = pos;
    const auto gcd = findGCD(std::abs(x), std::abs(y));
    return Pos {.xPos = (x / gcd), .yPos = (y / gcd)};
  }

  auto findLineStartingPoint(Pos referencePoint,
                             const Pos& gradient,
                             const auto& boundChecker) -> Pos
  {
    while (boundChecker.withinBounds(referencePoint - gradient)) {
      referencePoint = referencePoint - gradient;
    }

    return referencePoint;
  }

  auto intersectingPoints(const Pos& pos1,
                          const Pos& pos2,
                          const auto& boundChecker) -> Line_t
  {
    const auto gradient = gradientOf(calcDistance(pos1, pos2));
    const auto startingPoint =
        findLineStartingPoint(pos1, gradient, boundChecker);

    Line_t lineIntersection = {};
    auto currentPos = std::move(startingPoint);
    while (boundChecker.withinBounds(currentPos)) {
      const auto& [x, y] = currentPos;
      std::cout << "current position: ( x: " << x << ", y: " << y << " )\n";
      lineIntersection.push_back(currentPos);
      currentPos = currentPos + gradient;
    }

    return lineIntersection;
  }

}  // namespace

namespace std
{
  template<>
  struct hash<Pos>
  {
    auto operator()(const Pos& pos) const noexcept -> std::size_t
    {
      const auto& [x, y] = pos;
      const auto hash1 = hash<int32_t> {}(x);
      const auto hash2 = hash<int32_t> {}(y);
      return hash1 ^ hash2;
    }
  };
}  // namespace std

namespace solution
{
  auto solveProblem1(const std::string& input) -> uint32_t
  {
    const auto [boundChecker, antennaPosData] = createSolutionModel(input);
    std::unordered_set<Pos> uniqueAntiNodes;

    for (const auto& [_, positions] : antennaPosData) {
      for (auto i = 0u; i < positions.size(); i += 1) {
        const auto pos1 = positions[i];
        for (auto j {i + 1}; j < positions.size(); j += 1) {
          const auto pos2 = positions[j];
          const auto& [dx, dy] = calcDistance(pos1, pos2);
          const auto& [x1, y1] = pos1;
          const auto& [x2, y2] = pos2;
          const auto antiNode1Pos = Pos {x1 + dx, y1 + dy};  // Behind 1
          const auto antiNode2Pos = Pos {x2 - dx, y2 - dy};  // After 2
          if (boundChecker.withinBounds(antiNode1Pos)) {
            uniqueAntiNodes.insert(antiNode1Pos);
          }
          if (boundChecker.withinBounds(antiNode2Pos)) {
            uniqueAntiNodes.insert(antiNode2Pos);
          }
        }
      }
    }

    return uniqueAntiNodes.size();
  }

  auto solveProblem2(const std::string& input) -> uint32_t
  {
    const auto [boundChecker, antennaPosData] = createSolutionModel(input);
    std::unordered_set<Pos> uniqueAntiNodes;
    for (const auto& [_, positions] : antennaPosData) {
      for (auto i = 0u; i < positions.size(); i += 1) {
        const auto pos1 = positions[i];
        for (auto j {i + 1}; j < positions.size(); j += 1) {
          const auto pos2 = positions[j];
          const auto coordinatesOnLine =
              intersectingPoints(pos1, pos2, boundChecker);
          uniqueAntiNodes.insert(coordinatesOnLine.begin(),
                                 coordinatesOnLine.end());
        }
      }
    }

    std::cout << "Found following antinodes:\n";
    std::for_each(
        uniqueAntiNodes.begin(),
        uniqueAntiNodes.end(),
        [](const auto& pos)
        { std::cout << "( x: " << pos.xPos << ",y: " << pos.yPos << ")\n"; });

    return uniqueAntiNodes.size();
  }
}  // namespace solution
