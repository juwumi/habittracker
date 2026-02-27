#ifndef HABITTRACKER_TRACKER_H
#define HABITTRACKER_TRACKER_H
#include "habit.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

class habittracker {
private:
    std::vector<std::unique_ptr<Habit>> habits;

public:
    void addHabit(std::unique_ptr<Habit> habit) {
        habits.push_back(std::move(habit));
    }

    Habit* findHabit(const std::string& name) {
        auto it = std::find_if(habits.begin(), habits.end(),
            [&name](const std::unique_ptr<Habit>& h) {
                return h->getName() == name;
            });

        if (it != habits.end()) {
            return it->get();
        }
        return nullptr;
    }

    bool markHabitDone(const std::string& name, const std::string& date) {
        Habit* habit = findHabit(name);
        if (habit) {
            habit->markCompleted(date);
            return true;
        }
        return false;
    }

    bool removeHabit(const std::string& name) {
        auto it = std::find_if(habits.begin(), habits.end(),
            [&name](const std::unique_ptr<Habit>& h) {
                return h->getName() == name;
            });

        if (it != habits.end()) {
            habits.erase(it);
            return true;
        }
        return false;
    }

    const std::vector<std::unique_ptr<Habit>>& getHabits() const {
        return habits;
    }

    size_t size() const {
        return habits.size();
    }
};

#endif //HABITTRACKER_TRACKER_H