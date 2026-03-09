#include "booleanHabit.h"

booleanHabit::booleanHabit(const std::string &name, int targetDaysPerWeek):habit(name, targetDaysPerWeek){}

std::string booleanHabit::getType() const {
    return "booleanHabit";
}
std::string booleanHabit::toString() const {
    std::string last="Привычкм не была отмечена";
    if (history.size() > 0) {
        last=history.back()?"Выполнено":"Не выполнено";
    }
    return name + " | Серия: " + std::to_string(streak) + " | Последний день: " + last;
}



