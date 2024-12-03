package org.adventofcode.day3

import kotlin.test.Test
import org.junit.jupiter.api.Assertions.*

class Day3Test {
    companion object {
        const val INPUT = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"
    }
    
    @Test
    fun problem1Test() {
        var result = Solution.sumMulInstructions(INPUT)
        assertEquals(161, result)
    }
}
