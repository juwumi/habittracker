#ifndef HABITTRACKER_LOGMANAGER_H
#define HABITTRACKER_LOGMANAGER_H

#include "dailylog.h"
#include "storage.h"
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <algorithm>

class LogManager {
private:
    std::vector<std::unique_ptr<DailyLog>> logs;
    Storage& storage;
    int findLogIndex(const std::string& date) const;
    DailyLog* getOrCreateLog(const std::string& date);

public:
    explicit LogManager(Storage& s);
    std::string getTodayDate() const;
    void markDone(int habitId, std::variant<bool, int> value);
    void markDoneForDate(int habitId, const std::string& date, std::variant<bool, int> value);
    std::optional<std::variant<bool, int>> getTodayValue(int habitId) const;
    std::optional<std::variant<bool, int>> getValueForDate(int habitId, const std::string& date) const;
    bool isHabitDoneToday(int habitId) const;
    int countCompletionsInRange(int habitId, const std::string& start, const std::string& end) const;
    std::optional<DailyLog*> getLog(const std::string& date);
    std::vector<DailyLog*> getLogsInRange(const std::string& start, const std::string& end);
    void save();
    void load();
    const std::vector<std::unique_ptr<DailyLog>>& getAllLogs() const { return logs; }
    void clear();
};

#endif