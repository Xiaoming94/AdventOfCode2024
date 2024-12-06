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
    my_value = Solution.count_guard_steps(@input)
    assert_equal 41, my_value
  end
end
