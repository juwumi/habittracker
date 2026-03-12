#include "HabitTracker.h"
#include "storage.h"
#include "dailylog.h" 
#include "Statistics.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <memory>
#include "habit.h"
#include "booleanHabit.h"
#include "numericHabit.h"

HabitTracker::HabitTracker(std::unique_ptr<Storage> storage,
                           std::unique_ptr<DailyLog> logManager,
                           std::unique_ptr<Statistics> statistics)
    : m_storage(std::move(storage))
    , m_logManager(std::move(logManager))
    , m_statistics(std::move(statistics)) {
    std::cout << "HabitTracker created" << std::endl;
}

HabitTracker::~HabitTracker() = default;

void HabitTracker::createHabit(const std::string& name, HabitType type, int target, const std::string& unit) {
    std::cout << "Creating habit: " << name << std::endl;

    std::unique_ptr<habit> newHabit;

    if (type == HabitType::Boolean) {
        newHabit = std::make_unique<booleanHabit>(name);
    } else {
        newHabit = std::make_unique<numericHabit>(name, target, unit);
    }

    m_habits.push_back(std::move(newHabit));

    std::cout << "Habit saved in memory! Total habits: " << m_habits.size() << std::endl;
}

bool HabitTracker::deleteHabit(int habitId) {
    std::cout << "Deleting habit: " << habitId << std::endl;
    return false;
}

std::optional<habit*> HabitTracker::findHabit(int habitId) {
    for (auto& habit : m_habits) {
        if (habit->getId() == habitId) {
            return habit.get();
        }
    }
    return std::nullopt;
}

void HabitTracker::markHabitCompleted(int habitId, int value) {
    auto habitOpt = findHabit(habitId);
    if (!habitOpt.has_value()) {
        throw std::runtime_error("Habit not found");
    }

    habit* h = habitOpt.value();

    if (h->getType() == "numericHabit") {
        numericHabit* numHabit = dynamic_cast<numericHabit*>(h);
        if (numHabit) {
            numHabit->setValue(value);
        }
    } else {
        bool done = (value == 1);
        h->markCompleted(done);
    }

    m_statistics->incrementCounter();
    std::cout << "Progress recorded" << std::endl;
}

int HabitTracker::getCurrentStreak(int habitId) const {
    for (const auto& habit : m_habits) {
        if (habit->getId() == habitId) {
            return habit->getStreak();
        }
    }
    return 0;
}

double HabitTracker::getCompletionRate(int habitId, int days) const {
    for (const auto& habit : m_habits) {
        if (habit->getId() == habitId) {
            return habit->completionRate() * 100;
        }
    }
    return 0.0;
}

void HabitTracker::loadData() {
}

void HabitTracker::saveData() const {
}

