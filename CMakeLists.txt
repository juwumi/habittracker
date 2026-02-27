cmake_minimum_required(VERSION 3.20)
project(habittracker)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)

add_executable(habit_tracker
        src/main.cpp
        src/tracker.cpp
        src/logmanager.cpp
        include/tracker.h
        include/numeric_habit.h
        include/habit.h
        include/boolean_habit.h
)
