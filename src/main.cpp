#include <iostream>
#include <memory>
#include "dailylog.h"

int main() {
    std::cout << "Test DailyLog\n";

    auto log = std::make_unique<DailyLog>("2026-02-27");
    std::cout << "Log created for date: " << log->getDate() << "\n";

    log->addEntry("habit1", true);
    log->addEntry("habit2", 5000);
    log->addEntry("habit3", false);

    std::cout << "Entries added\n";

    std::cout << "Do we have habit1? " << (log->hasEntry("habit1") ? "yes" : "no") << "\n";
    std::cout << "Do we have habit4? " << (log->hasEntry("habit4") ? "yes" : "no") << "\n";

    auto entry1 = log->getEntry("habit1");
    if (entry1.has_value()) {
        std::cout << "habit1 = ";
        std::visit([](const auto& v) { std::cout << v; }, entry1.value());
        std::cout << "\n";
    }

    auto entry2 = log->getEntry("habit2");
    if (entry2.has_value()) {
        std::cout << "habit2 = ";
        std::visit([](const auto& v) { std::cout << v; }, entry2.value());
        std::cout << "\n";
    }

    std::string serialized = log->serialize();
    std::cout << "Serialized string: " << serialized << "\n";

    auto restoredLog = DailyLog::deserialize(serialized);
    std::cout << "Log for the date has been restored: " << restoredLog->getDate() << "\n";

    auto restoredEntry = restoredLog->getEntry("habit1");
    if (restoredEntry.has_value()) {
        std::cout << "Restored habit1 = ";
        std::visit([](const auto& v) { std::cout << v; }, restoredEntry.value());
        std::cout << "\n";
    }

    return 0;
}