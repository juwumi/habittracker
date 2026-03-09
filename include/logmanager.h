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
    std::string getTodayDate() const;
    int findLogIndex(const std::string& date) const;
    DailyLog* getOrCreateLog(const std::string& date);
public:
    explicit LogManager(Storage& s);
    void markDone(const std::string& habitId, std::variant<bool, int> value);
    void markDoneForDate(const std::string& habitId,
                         const std::string& date,
                         std::variant<bool, int> value);
    std::optional<DailyLog*> getLog(const std::string& date);
    std::optional<std::variant<bool, int>> getTodayValue(const std::string& habitId) const;
    std::optional<std::variant<bool, int>> getValueForDate(
        const std::string& habitId,
        const std::string& date) const;
    std::vector<DailyLog*> getLogsInRange(const std::string& start,
                                           const std::string& end);
    bool isHabitDoneToday(const std::string& habitId) const;
    int countCompletionsInRange(const std::string& habitId,
                                 const std::string& start,
                                 const std::string& end) const;
    void save();
    void load();
    const std::vector<std::unique_ptr<DailyLog>>& getAllLogs() const { return logs; }
    void clear();
};

#endif //HABITTRACKER_LOGMANAGER_H