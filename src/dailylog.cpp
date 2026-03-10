#include "dailylog.h"
#include <sstream>

DailyLog::DailyLog(const std::string& logDate) : date(logDate) {}

void DailyLog::addEntry(int habitId, std::variant<bool, int> value) {
    entries[habitId] = value;
}

std::optional<std::variant<bool, int>> DailyLog::getEntry(int habitId) const {
    auto it = entries.find(habitId);
    if (it != entries.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool DailyLog::hasEntry(int habitId) const {
    return entries.find(habitId) != entries.end();
}

std::string DailyLog::getDate() const {
    return date;
}

const std::map<int, std::variant<bool, int>>& DailyLog::getAllEntries() const {
    return entries;
}

std::string DailyLog::serialize() const {
    std::stringstream ss;
    ss << date << "|";
    bool first = true;
    for (const auto& [habitId, value] : entries) {
        if (!first) {
            ss << ",";
        }
        first = false;
        ss << habitId << ":";
        std::visit([&ss](const auto& v) {
            ss << v;
        }, value);
    }

    return ss.str();
}

std::unique_ptr<DailyLog> DailyLog::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string datePart;
    std::string entriesPart;

    std::getline(ss, datePart, '|');
    std::getline(ss, entriesPart);

    auto log = std::make_unique<DailyLog>(datePart);

    if (entriesPart.empty()) {
        return log;
    }

    std::stringstream entryStream(entriesPart);
    std::string entry;

    while (std::getline(entryStream, entry, ',')) {
        size_t colonPos = entry.find(':');

        if (colonPos == std::string::npos) {
            continue;
        }

        std::string habitIdStr = entry.substr(0, colonPos);
        std::string valueStr = entry.substr(colonPos + 1);

        int habitId = std::stoi(habitIdStr);

        bool isNumber = true;
        for (char c : valueStr) {
            if (!isdigit(c) && c != '-') {
                isNumber = false;
                break;
            }
        }

        if (isNumber) {
            int intValue = std::stoi(valueStr);
            if (valueStr == "0" || valueStr == "1") {
                bool boolValue = (intValue == 1);
                log->addEntry(habitId, boolValue);
            } else {
                log->addEntry(habitId, intValue);
            }
        } else {
            if (valueStr == "true") {
                log->addEntry(habitId, true);
            } else if (valueStr == "false") {
                log->addEntry(habitId, false);
            }
        }
    }

    return log;
}