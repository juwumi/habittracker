#ifndef NUMERICHABIT_H
#define NUMERICHABIT_H

#include "habit.h"

class numericHabit : public habit {
private:
    double goal;
    double currentValue=0;
    std::string unit;
public:
    numericHabit(const std::string& name, double goal, const std::string& unit= "", int targetDaysPerWeek=7);

    std::string getType() const override;
    std::string toString() const override;

    void setValue(double value);

    double getGoal() const {return goal;}
    double getCurrentValue() const {return currentValue;}
    std::string getUnit() const {return unit;}
    bool isGoalReached() const {return currentValue>=goal;}
    std::optional<double> getProgress() const;
};

#endif