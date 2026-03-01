#include "dailylog.h"
#include <sstream>

DailyLog::DailyLog(const std::string& logDate) : date(logDate) {}

void DailyLog::addEntry(const std::string& habitId, std::variant<bool, int> value) {
    entries[habitId] = value;
}

std::optional<std::variant<bool, int>> DailyLog::getEntry(const std::string& habitId) const {
    auto it = entries.find(habitId);
    if (it != entries.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool DailyLog::hasEntry(const std::string& habitId) const {
    return entries.find(habitId) != entries.end();
}

std::string DailyLog::getDate() const {
    return date;
}

const std::map<std::string, std::variant<bool, int>>& DailyLog::getAllEntries() const {
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

    if (!entriesPart.empty()) {
        std::stringstream entryStream(entriesPart);
        std::string entry;

        while (std::getline(entryStream, entry, ',')) {
            size_t colonPos = entry.find(':');
            if (colonPos != std::string::npos) {
                std::string habitId = entry.substr(0, colonPos);
                std::string valueStr = entry.substr(colonPos + 1);

                try {
                    int intValue = std::stoi(valueStr);
                    log->addEntry(habitId, intValue);
                } catch (...) {
                    bool boolValue = (valueStr == "1");
                    log->addEntry(habitId, boolValue);
                }
            }
        }
    }

    return log;
}