cmake_minimum_required(VERSION 3.14)
project(AdventOfCode_day5 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    day5_exec
    src/main.cpp
    src/SolutionsImpl.cpp
)

target_include_directories(
    day5_exec
    PRIVATE inc/
)

add_executable(
    day5_test
    tests/day5Tests.cpp
    src/SolutionsImpl.cpp
)

target_include_directories(
    day5_test
    PRIVATE inc/
)

target_link_libraries(
    day5_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day5_test)
