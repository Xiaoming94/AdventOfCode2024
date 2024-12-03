package org.adventofcode.day3

import java.util.Scanner

class Main {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            var input = String()
            val sc = Scanner(System.`in`)

            do {
                val line = sc.nextLine()
                input += (line + "\n")
            } while (sc.hasNext())
            println("Input is:\n" + input)
            println("Problem1 Solution: " + Solution.sumMulInstructions(input))
            println("Problem2 Solution: " + Solution.sumMulInstructionsWithDos(input))
        }
    }
}
