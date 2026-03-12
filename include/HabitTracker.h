#ifndef HABITTRACKER_H
#define HABITTRACKER_H

#include "Types.h"
#include "Types.h"
#include "habit.h"
#include "booleanHabit.h"
#include "numericHabit.h"
#include "storage.h"
#include "dailylog.h"
#include "Statistics.h"
#include <memory>
#include <vector>
#include <string>
#include <optional>


class HabitTracker {
public:
    HabitTracker(std::unique_ptr<Storage> storage, 
                 std::unique_ptr<DailyLog> logManager,
                 std::unique_ptr<Statistics> statistics);
    
    ~HabitTracker();

    HabitTracker(const HabitTracker&) = delete;
    HabitTracker& operator=(const HabitTracker&) = delete;
    HabitTracker(HabitTracker&&) = default;
    HabitTracker& operator=(HabitTracker&&) = default;

    void createHabit(const std::string& name, HabitType type, int target = 1);
    bool deleteHabit(int habitId);
    std::optional<habit*> findHabit(int habitId);
    void markHabitCompleted(int habitId, int value = 1);
    
    int getCurrentStreak(int habitId) const;
    double getCompletionRate(int habitId, int days) const;
    
    void loadData();
    void saveData() const;

private:
    std::unique_ptr<Storage> m_storage;
    std::unique_ptr<DailyLog> m_logManager;
    std::unique_ptr<Statistics> m_statistics;
    std::vector<std::unique_ptr<habit>> m_habits;
};

#endif