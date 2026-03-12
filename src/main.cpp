#include <iostream>
#include <memory>
#include <string>
#include "habit.h"
#include "booleanHabit.h"
#include "numericHabit.h"
#include "storage.h"
#include "dailylog.h"
#include "ConsoleUI.h"
#include "HabitTracker.h"
#include "Statistics.h"
#include "Types.h"
int main() {
    std::cout << "\n";
    std::cout << "         HABIT TRACKER PROJECT            \n";
    std::cout << "\n";
    
    try {
        auto storage = std::make_unique<Storage>("habits_data.txt");

        auto logManager = std::make_unique<DailyLog>("2026-03-12");

        auto statistics = std::make_unique<Statistics>();

        auto tracker = std::make_unique<HabitTracker>(
            std::move(storage),
            std::move(logManager),
            std::move(statistics)
        );
        
        std::cout << "All components loaded successfully!\n";
        std::cout << "\n";
        std::cout << "   Starting Habit Tracker       \n";
        std::cout << "\n";
        
        ConsoleUI ui(std::move(tracker));
        ui.run();
        
    } catch (const std::exception& e) {
        std::cerr << "\n";
        std::cerr << "             ERROR OCCURRED               \n";
        std::cerr << "\n";
        return 1;
    }
    
    std::cout << "\n";
    std::cout << "       Thank you for using!               \n";
    std::cout << "           Goodbye!                        \n";
    std::cout << "\n";
    
    return 0;
}