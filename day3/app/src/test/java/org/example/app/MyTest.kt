package org.example.app

import kotlin.test.Test
import org.junit.jupiter.api.Assertions.*

class MyTest() {
    @Test
    fun myJunitTest() {
        val myVal = 1337
        assertEquals(1337, myVal)
    }
}
