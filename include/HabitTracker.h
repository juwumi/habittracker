#include "HabitTracker.h"
#include "Storage.h"
#include "LogManager.h"
#include "Statistics.h"
#include <algorithm>
#include <iostream>

HabitTracker::HabitTracker(std::unique_ptr<Storage> storage,
                           std::unique_ptr<LogManager> logManager,
                           std::unique_ptr<Statistics> statistics)
    : m_storage(std::move(storage))
    , m_logManager(std::move(logManager))
    , m_statistics(std::move(statistics)) {
    std::cout << "HabitTracker created" << std::endl;
}

HabitTracker::~HabitTracker() = default;

void HabitTracker::createHabit(const std::string& name, HabitType type, int target) {
    std::cout << "Creating habit: " << name << std::endl;
}

bool HabitTracker::deleteHabit(int habitId) {
    for (auto it = m_habits.begin(); it != m_habits.end(); ++it) {
        if ((*it)->getId() == habitId) {
            m_habits.erase(it);
            return true;
        }
    }
    return false;
}

std::optional<Habit*> HabitTracker::findHabit(int habitId) {
    for (auto& habit : m_habits) {
        if (habit->getId() == habitId) {
            return habit.get();
        }
    }

}

void HabitTracker::markHabitCompleted(int habitId, int value) {
    auto habitOpt = findHabit(habitId);
    if (!habitOpt.has_value()) {
        std::cout << "Habit not found" << std::endl;
        return;
    }
    
    Habit* habit = habitOpt.value();
    std::cout << "Marking habit completed: " << habitId << std::endl;
}

int HabitTracker::getCurrentStreak(int habitId) const {
    return 0;
}

double HabitTracker::getCompletionRate(int habitId, int days) const {
    return 0.0;
}

void HabitTracker::loadData() {
    std::cout << "Loading data..." << std::endl;
}

void HabitTracker::saveData() const {
    std::cout << "Saving data..." << std::endl;
}