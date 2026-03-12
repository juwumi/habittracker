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

void HabitTracker::createHabit(const std::string& name, HabitType type, int target) {
    std::cout << "Creating habit: " << name << std::endl;
}

bool HabitTracker::deleteHabit(int habitId) {
    std::cout << "Deleting habit: " << habitId << std::endl;
    return false;
}

std::optional<habit*> HabitTracker::findHabit(int habitId) {
    return std::nullopt;
}

void HabitTracker::markHabitCompleted(int habitId, int value) {
    auto habitOpt = findHabit(habitId);
    if (!habitOpt.has_value()) {
        throw std::runtime_error("Habit not found");
    }
    m_statistics->incrementCounter();
    std::cout << "Marking habit " << habitId << " as completed" << std::endl;
}

int HabitTracker::getCurrentStreak(int habitId) const {
    return 0;
}

double HabitTracker::getCompletionRate(int habitId, int days) const {
    return 0.0;
}

void HabitTracker::loadData() {
}

void HabitTracker::saveData() const {
}