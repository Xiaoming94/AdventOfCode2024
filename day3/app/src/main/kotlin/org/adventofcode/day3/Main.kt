package org.adventofcode.day3

import java.util.Scanner

class Main {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            println("Running")
            var input = String()
            val sc = Scanner(System.`in`)

            var line = ""
            do {
                line = sc.nextLine()
                input += line
            } while (sc.hasNext())
            println("Done" + input)
        }
    }
}
