#include "booleanHabit.h"

booleanHabit::booleanHabit(const std::string &name, int targetDaysPerWeek):habit(name, targetDaysPerWeek){}

std::string booleanHabit::getType() const {
    return "booleanHabit";
}
std::string booleanHabit::toString() const {
    std::string last="the habit wasn't marked";
    if (history.size() > 0) {
        last=history.back()?"done":"not done";
    }
    return name + " | streak: " + std::to_string(streak) + " | last day: " + last;
}



