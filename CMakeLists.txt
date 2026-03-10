cmake_minimum_required(VERSION 3.20)
project(habittracker)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)

add_executable(habit_tracker
        src/main.cpp
        include/dailylog.h
        src/dailylog.cpp
        src/main.cpp
        include/storage.h
        src/storage.cpp
        include/logmanager.h
        src/logmanager.cpp
)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(tests
        tests/tests.cpp
        src/habit.cpp
        src/booleanHabit.cpp
        src/numericHabit.cpp
)

target_link_libraries(tests
        GTest::gtest_main
)

target_include_directories(tests PRIVATE include)

include(GoogleTest)
gtest_discover_tests(tests)