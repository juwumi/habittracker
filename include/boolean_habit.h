#ifndef HABITTRACKER_BOOLEAN_HABIT_H
#define HABITTRACKER_BOOLEAN_HABIT_H

#include "habit.h"

class BooleanHabit : public Habit {
public:
    BooleanHabit(const std::string& name) : Habit(name) {}

    std::string getType() const override { return "boolean"; }
    void markCompleted(const std::string& date) override {
        (void)date;
    }
};
#endif //HABITTRACKER_BOOLEAN_HABIT_H