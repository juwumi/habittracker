#include "numericHabit.h"

numericHabit::numericHabit(const std::string &name, double goal, const std::string &unit, int targetDaysPerWeek)
    : habit(name, targetDaysPerWeek), goal(goal), unit(unit) {
    if (goal<0) {
        throw HabitException("Goal is negative");
    }
}

std::string numericHabit::getType() const {
    return "numericHabit";
}

void numericHabit::setValue(double value) {
    currentValue=value;
    markCompleted(value>=goal);
}

std::optional<double> numericHabit::getProgress() const {
    if (goal==0) return std::nullopt;
    return (currentValue/goal)*100;
}

std::string numericHabit::toString() const {
    std::string status=isGoalReached()?"reached":"not reached";
    return getName() + "| goal: " + std::to_string(goal) + " " + unit + " | now: " + std::to_string(currentValue) + " " + unit + " |  " + status;
}


