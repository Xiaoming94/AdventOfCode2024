package org.adventofcode.day3

import java.util.regex.Pattern

class Solution {
    companion object {
        fun sumMulInstructions(input: String): Int {

            val instructionList: List<MulInstruction> = findMulInstructions(input)
            return instructionList.map { instruction -> instruction.execute() }.sum()
        }

        fun sumMulInstructionsWithDos(input: String): Int {

            val dontPattern: Pattern = Pattern.compile("don't\\(\\)")
            val subInstructions: List<String> = input.split(dontPattern)
            var instructionList: List<MulInstruction> = findMulInstructions(subInstructions[0])
            val doPattern: Pattern = Pattern.compile("do\\(\\)")

            for (i in (1 ..< subInstructions.size)) {
                val enabled = subInstructions[i].split(doPattern)
                for (j in (1 ..< enabled.size)) {
                    instructionList += findMulInstructions(enabled[j])
                }
            }
            return instructionList.map { instruction -> instruction.execute() }.sum()
        }

        private fun findMulInstructions(input: String): List<MulInstruction> {
            val instructionPattern: Pattern = Pattern.compile("mul\\([0-9]+,[0-9]+\\)")
            val matches = instructionPattern.matcher(input)
            var instructionList: List<MulInstruction> = mutableListOf()
            while (matches.find()) {
                val operandMatcher: Pattern = Pattern.compile("[0-9]+")
                val operandMatches = operandMatcher.matcher(matches.group())
                try {
                    if (operandMatches.find()) {
                        val operand1 = operandMatches.group().toInt()
                        if (operandMatches.find()) {
                            val operand2 = operandMatches.group().toInt()
                            instructionList += (MulInstruction(operand1, operand2))
                        }
                    }
                } catch (e: NumberFormatException) {
                    println("IllegalInput")
                }
            }

            return instructionList
        }
    }
}

class MulInstruction(operand1: Int, operand2: Int) {
    val operand1 = operand1
    val operand2 = operand2
    fun execute(): Int {
        return operand1 * operand2
    }
}
