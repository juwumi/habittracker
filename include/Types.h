#ifndef TYPES_H
#define TYPES_H

#include <chrono>
#include <string>

enum class HabitType {
    Boolean,
    Numeric
};

enum class HabitStatus {
    Active,
    Archived
};

struct DailyProgress {
    int habitId;
    bool isCompleted;
    int currentValue;
    int targetValue;
    std::chrono::system_clock::time_point date;
    
    DailyProgress() : habitId(0), isCompleted(false), currentValue(0), targetValue(0) {}
};

#endif