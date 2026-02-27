#ifndef HABITTRACKER_HABIT_H
#define HABITTRACKER_HABIT_H

#include <string>
#include <chrono>

class Habit {
protected:
    std::string id;
    std::string name;
    std::chrono::system_clock::time_point createdDate;

public:
    Habit(const std::string& habitName) : name(habitName) {
        createdDate = std::chrono::system_clock::now();
        id = "temp_" + std::to_string(rand());
    }

    virtual ~Habit() = default;

    virtual std::string getType() const { return "unknown"; }
    virtual void markCompleted(const std::string& date) {
        (void) date;
    }

    std::string getName() const { return name; }
    std::string getId() const { return id; }
};

#endif //HABITTRACKER_HABIT_H