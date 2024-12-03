package org.adventofcode.day3

import kotlin.test.Test
import org.junit.jupiter.api.Assertions.*

class Day3Test {

    @Test
    fun problem1Test() {
        val INPUT = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
        var result = Solution.sumMulInstructions(INPUT)
        assertEquals(161, result)
    }

    @Test
    fun problem2Test() {
        val input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5));"
        var result = Solution.sumMulInstructionsWithDos(input)
        assertEquals(48, result)
    }
}
