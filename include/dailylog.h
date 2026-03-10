#ifndef HABITTRACKER_DAILYLOG_H
#define HABITTRACKER_DAILYLOG_H

#include <string>
#include <map>
#include <variant>
#include <optional>
#include <memory>
#include <sstream>

class DailyLog {
private:
    std::string date;
    std::map<int, std::variant<bool, int>> entries;

public:
    explicit DailyLog(const std::string& logDate);

    void addEntry(int habitId, std::variant<bool, int> value);
    std::optional<std::variant<bool, int>> getEntry(int habitId) const;
    bool hasEntry(int habitId) const;

    std::string getDate() const;
    const std::map<int, std::variant<bool, int>>& getAllEntries() const;

    std::string serialize() const;
    static std::unique_ptr<DailyLog> deserialize(const std::string& data);
};

#endif