#include "ConsoleUI.h"
#include "habit.h" 
#include <iostream>
#include <limits>
#include <iomanip>

ConsoleUI::ConsoleUI(std::unique_ptr<HabitTracker> tracker)
    : m_tracker(std::move(tracker))
    , m_isRunning(true) {
}

void ConsoleUI::run() {
    m_tracker->loadData();
    
    while (m_isRunning) {
        try {
            showMainMenu();
            
            int choice;
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            
            handleUserInput(choice);
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    
    m_tracker->saveData();
}

void ConsoleUI::showMainMenu() {
    std::cout << "\n           MAIN MENU            \n";
    std::cout << "1. Show all habits\n";
    std::cout << "2. Create new habit\n";
    std::cout << "3. Mark habit completed\n";
    std::cout << "4. View statistics\n";
    std::cout << "5. Exit\n";
    std::cout << "------------------------\n";
    std::cout << "Choice: ";
}

void ConsoleUI::handleUserInput(int choice) {
    switch(choice) {
        case 1: displayAllHabits(); break;
        case 2: createHabitScreen(); break;
        case 3: markHabitScreen(); break;
        case 4: showStatisticsScreen(); break;
        case 5: m_isRunning = false; break;
        default: std::cout << "Invalid choice. Please try again.\n";
    }
}

void ConsoleUI::displayAllHabits() {
    std::cout << "\n   All Habits   \n";
    
    std::cout << "1. Drink water [Boolean] - Streak: 5 days\n";
    std::cout << "2. Running [Numeric] - 3/7 km\n";
    std::cout << "3. Read book [Boolean] - Streak: 2 days\n";
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleUI::createHabitScreen() {
    std::cout << "\n    Create New Habit   \n";
    
    std::string name;
    int typeChoice;
    int target = 1;
    
    std::cout << "Enter habit name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    
    std::cout << "Habit type:\n";
    std::cout << "1. Boolean (done/not done)\n";
    std::cout << "2. Numeric (with target value)\n";
    std::cout << "Choice: ";
    std::cin >> typeChoice;
    
    HabitType type;
    if (typeChoice == 1) {
        type = HabitType::Boolean;
    } else {
        type = HabitType::Numeric;
        std::cout << "Enter target value: ";
        std::cin >> target;
    }
    
    m_tracker->createHabit(name, type, target);
    std::cout << "Habit created successfully!\n";
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleUI::markHabitScreen() {
    std::cout << "\n    Mark Habit Completed    \n";
    
    int habitId;
    int value = 1;
    
    std::cout << "Enter habit ID: ";
    std::cin >> habitId;
    
    std::cout << "Enter value (for numeric habits): ";
    std::cin >> value;
    
    try {
        m_tracker->markHabitCompleted(habitId, value);
        std::cout << "Progress recorded!\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleUI::showStatisticsScreen() {
    std::cout << "\n    Statistics    \n";
    
    int habitId;
    std::cout << "Enter habit ID: ";
    std::cin >> habitId;
    
    int streak = m_tracker->getCurrentStreak(habitId);
    double rate = m_tracker->getCompletionRate(habitId, 7);
    
    std::cout << "Current streak: " << streak << " days\n";
    std::cout << "Completion rate (7 days): " << std::fixed << std::setprecision(1) << rate << "%\n";
    
    showProgressBar(rate);
    std::cout << "\n";
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleUI::showProgressBar(double percentage) {
    int barWidth = 50;
    std::cout << "\nProgress: [";
    
    int pos = static_cast<int>(barWidth * percentage / 100.0);
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << percentage << "%\n";
}