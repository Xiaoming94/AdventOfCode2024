# frozen_string

require 'minitest/autorun'
require_relative '../src/solution'

class Day6Tests < Minitest::Test
  def test_framework
    my_value = Solution.my_const_value
    assert_equal 42, my_value
  end
end
