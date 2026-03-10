#ifndef HABITTRACKER_H
#define HABITTRACKER_H

#include "Types.h"
#include <memory>
#include <vector>
#include <string>
#include <optional>

class Habit;
class LogManager;
class Storage;
class Statistics;

class HabitTracker {
public:
    HabitTracker(std::unique_ptr<Storage> storage, 
                 std::unique_ptr<LogManager> logManager,
                 std::unique_ptr<Statistics> statistics);
    
    ~HabitTracker();

    HabitTracker(const HabitTracker&) = delete;
    HabitTracker& operator=(const HabitTracker&) = delete;
    HabitTracker(HabitTracker&&) = default;
    HabitTracker& operator=(HabitTracker&&) = default;

    void createHabit(const std::string& name, HabitType type, int target = 1);
    bool deleteHabit(int habitId);
    std::optional<Habit*> findHabit(int habitId);
    void markHabitCompleted(int habitId, int value = 1);
    
    int getCurrentStreak(int habitId) const;
    double getCompletionRate(int habitId, int days) const;
    
    void loadData();
    void saveData() const;

private:
    std::unique_ptr<Storage> m_storage;
    std::unique_ptr<LogManager> m_logManager;
    std::unique_ptr<Statistics> m_statistics;
    std::vector<std::unique_ptr<Habit>> m_habits;
};

#endif