#ifndef HABIT_H
#define HABIT_H

#include <string>
#include<vector>
#include <optional>
#include <stdexcept>

class HabitException: public std::runtime_error {
public:
    explicit HabitException(const std::string& message): std::runtime_error(message){};

};

class Habit{
protected:
    std::string name;
    int streak=0;
    int targetDaysPerWeek=7;
    std::vector<bool> history;
public:
    explicit Habit(const std::string& name, int targetDaysPerWeek=7);
    virtual ~Habit()=default;

    virtual std::string getType() const = 0;
    virtual std::string toString() const=0;

    void markCompleted(bool done);
    void updateStreak();
    double completionRate() const;
    std::optional <bool> getLastEntry() const;

    std::string getName() const { return name; }
    int getStreak() const { return streak; }
    const std::vector<bool>& getHistory() const { return history; }
    int getTargetDaysPerWeek() const { return targetDaysPerWeek; }
};
#endif
