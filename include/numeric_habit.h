#ifndef HABITTRACKER_NUMERIC_HABIT_H
#define HABITTRACKER_NUMERIC_HABIT_H

#include "habit.h"

class NumericHabit : public Habit {
public:
    NumericHabit(const std::string& name, int target, const std::string& unit)
        : Habit(name) {}

    std::string getType() const override { return "numeric"; }
    void markCompleted(const std::string& date) override {}
    void markWithValue(const std::string& date, int value) {}
};

#endif //HABITTRACKER_NUMERIC_HABIT_H