#include <cmath>
#include <cstdint>
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

    auto operator==(const Pos& other) const -> bool
    {
      return xPos == other.xPos && yPos == other.yPos;
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
    const auto& [boundChecker, antennaPosData] = createSolutionModel(input);
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
}  // namespace solution
