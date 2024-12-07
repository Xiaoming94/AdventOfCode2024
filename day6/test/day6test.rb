# frozen_string

require 'minitest/autorun'
require_relative '../src/solution'

class Day6Tests < Minitest::Test
  def setup
    @input = "....#.....\n"\
             ".........#\n"\
             "..........\n"\
             "..#.......\n"\
             ".......#..\n"\
             "..........\n"\
             ".#..^.....\n"\
             "........#.\n"\
             "#.........\n"\
             '......#...'
  end

  def test_problem1solution
    result = Solution.count_guard_steps(@input)
    assert_equal 41, result
  end

  def test_problem2solution
    result = Solution.find_possible_cycles(@input)
    assert_equal 6, result
  end
end
