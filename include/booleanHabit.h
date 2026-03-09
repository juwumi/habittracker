#ifndef BOOLEANHABIT_H
#define BOOLEANHABIT_H

#include "habit.h"

class booleanHabit : public habit {
private:
    bool goal=true;
public:
    explicit booleanHabit(const std::string& name, int targetDaysPerWeek=7);
    std::string getType() const override;
    std::string toString() const override;
    static constexpr bool defaultGoal(){return true;}
};






#endif