#include "logmanager.h"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

LogManager::LogManager(Storage& s) : storage(s) {
    load();
}
std::string LogManager::getTodayDate() const {
    auto now = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&tt);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d");
    return ss.str();
}
int LogManager::findLogIndex(const std::string& date) const {
    for (size_t i = 0; i < logs.size(); ++i) {
        if (logs[i]->getDate() == date) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
DailyLog* LogManager::getOrCreateLog(const std::string& date) {
    int index = findLogIndex(date);
    if (index != -1) {
        return logs[index].get();
    }
    auto newLog = std::make_unique<DailyLog>(date);
    DailyLog* ptr = newLog.get();
    logs.push_back(std::move(newLog));
    std::sort(logs.begin(), logs.end(),
        [](const auto& a, const auto& b) {
            return a->getDate() < b->getDate();
        });
    return ptr;
}
void LogManager::markDone(const std::string& habitId, std::variant<bool, int> value) {
    std::string today = getTodayDate();
    auto* log = getOrCreateLog(today);
    log->addEntry(habitId, value);
    save();
}
void LogManager::markDoneForDate(const std::string& habitId,
                                  const std::string& date,
                                  std::variant<bool, int> value) {
    auto* log = getOrCreateLog(date);
    log->addEntry(habitId, value);
    save();
}
std::optional<DailyLog*> LogManager::getLog(const std::string& date) {
    int index = findLogIndex(date);
    if (index != -1) {
        return logs[index].get();
    }
    return std::nullopt;
}
std::optional<std::variant<bool, int>> LogManager::getTodayValue(
    const std::string& habitId) const {
    std::string today = getTodayDate();
    return getValueForDate(habitId, today);
}
std::optional<std::variant<bool, int>> LogManager::getValueForDate(
    const std::string& habitId,
    const std::string& date) const {
    int index = findLogIndex(date);
    if (index != -1) {
        return logs[index]->getEntry(habitId);
    }
    return std::nullopt;
}
std::vector<DailyLog*> LogManager::getLogsInRange(const std::string& start,
                                                   const std::string& end) {
    std::vector<DailyLog*> result;
    for (auto& log : logs) {
        if (log->getDate() >= start && log->getDate() <= end) {
            result.push_back(log.get());
        }
    }
    return result;
}
bool LogManager::isHabitDoneToday(const std::string& habitId) const {
    auto value = getTodayValue(habitId);
    if (value.has_value()) {
        if (std::holds_alternative<bool>(value.value())) {
            return std::get<bool>(value.value());
        }
    }
    return false;
}
int LogManager::countCompletionsInRange(const std::string& habitId,
                                         const std::string& start,
                                         const std::string& end) const {
    int count = 0;
    for (const auto& log : logs) {
        if (log->getDate() >= start && log->getDate() <= end) {
            auto entry = log->getEntry(habitId);
            if (entry.has_value() && std::holds_alternative<bool>(entry.value())) {
                if (std::get<bool>(entry.value())) {
                    count++;
                }
            }
        }
    }
    return count;
}
void LogManager::save() {
    storage.saveLogs(logs);
}
void LogManager::load() {
    auto loaded = storage.loadLogs();
    if (loaded.has_value()) {
        logs = std::move(loaded.value());
    }
}
void LogManager::clear() {
    logs.clear();
    save();
}