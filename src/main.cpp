#include <iostream>
#include <memory>
#include "dailylog.h"
#include "storage.h"
#include "logmanager.h"

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
    std::cout << "TEST LOGMANAGER\n";
    try {
        Storage storage("habits_data.txt");
        LogManager logManager(storage);
        std::cout << "\nMark habits for today:\n";
        logManager.markDone("exercise", true);
        logManager.markDone("water", 8);
        logManager.markDone("reading", true);
        logManager.markDoneForDate("exercise", "2026-03-08", true);
        logManager.markDoneForDate("water", "2026-03-08", 6);
        std::cout << "\nChecking values:\n";
        auto todayExercise = logManager.getTodayValue("exercise");
        if (todayExercise.has_value()) {
            std::cout << "exercise today: ";
            std::visit([](const auto& v) { std::cout << v; }, todayExercise.value());
            std::cout << "\n";
        }
        auto yesterdayWater = logManager.getValueForDate("water", "2026-03-08");
        if (yesterdayWater.has_value()) {
            std::cout << "water 2026-03-08: ";
            std::visit([](const auto& v) { std::cout << v; }, yesterdayWater.value());
            std::cout << "\n";
        }
        std::cout << "\nExecution status today:\n";
        std::cout << "exercise: " << (logManager.isHabitDoneToday("exercise") ? "yes" : "no") << "\n";
        std::cout << "reading: " << (logManager.isHabitDoneToday("reading") ? "yes" : "no") << "\n";
        std::cout << "\nLogs for the period 2026-03-08 - 2026-03-09:\n";
        auto rangeLogs = logManager.getLogsInRange("2026-03-08", "2026-03-09");
        for (auto log : rangeLogs) {
            printLog(log);
        }
        int exerciseCount = logManager.countCompletionsInRange("exercise", "2026-03-01", "2026-03-09");
        std::cout << "\nNumber of executions of exercise for March: " << exerciseCount << "\n";
        logManager.save();
        LogManager newManager(storage);
        std::cout << "Logs loaded: " << newManager.getAllLogs().size() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}