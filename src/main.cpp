#include <iostream>
#include <memory>
#include <vector>
#include "dailylog.h"
#include "storage.h"

void printLog(const DailyLog* log) {
    if (!log) return;

    std::cout << "Date: " << log->getDate() << "\n";
    for (const auto& [habitId, value] : log->getAllEntries()) {
        std::cout << "  " << habitId << " = ";
        std::visit([](const auto& v) { std::cout << v; }, value);
        std::cout << "\n";
    }
}

int main() {
    std::cout << "TEST STORAGE\n";
    try {
        std::vector<std::unique_ptr<DailyLog>> logs;
        auto log1 = std::make_unique<DailyLog>("2026-02-27");
        log1->addEntry("habit1", true);
        log1->addEntry("habit2", 5000);
        logs.push_back(std::move(log1));

        auto log2 = std::make_unique<DailyLog>("2026-02-28");
        log2->addEntry("habit1", false);
        log2->addEntry("habit2", 7500);
        logs.push_back(std::move(log2));

        std::cout << "Created " << logs.size() << " logs\n";

        Storage storage("test_logs.txt");
        storage.saveLogs(logs);

        auto loadedLogs = storage.loadLogs();

        if (loadedLogs.has_value()) {
            std::cout << "\nDown loaded " << loadedLogs->size() << " logs:\n";
            for (const auto& log : loadedLogs.value()) {
                printLog(log.get());
            }
        } else {
            std::cout << "Fail does not find (first launch)\n";
        }

        Storage emptyStorage("non_existent_file.txt");
        auto result = emptyStorage.loadLogs();
        if (!result.has_value()) {
            std::cout << "\nOK: Fail does not exist. Returned nullopt\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}