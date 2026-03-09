#include "booleanHabit.h"
#include <string>

booleanHabit::booleanHabit(const std::string &name, int targetDaysPerWeek):habit(name, targetDaysPerWeek){}

std::string booleanHabit::getType() const {
    return "booleanHabit";
}
std::string booleanHabit::toString() const {
    std::string last="the habit wasn't marked";
    if (getHistory().size() > 0) {
        last=getHistory().back()?"done":"not done";
    }

    std::string goalType= goal ? "(should do)" : "(should avoid)";
    return getName() + " | streak: " + std::to_string(getStreak()) + " | last day: " + last;
}



