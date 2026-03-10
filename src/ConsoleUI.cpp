#include "ConsoleUI.h"
#include <iostream>
#include <limits>

ConsoleUI::ConsoleUI(std::unique_ptr<HabitTracker> tracker)
    : m_tracker(std::move(tracker))
    , m_isRunning(true) {
}

void ConsoleUI::run() {
    std::cout << "=== Habit Tracker ===\n";
    m_tracker->loadData();
    
    while (m_isRunning) {
        showMainMenu();
        
        int choice;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
            continue;
        }
        
        handleUserInput(choice);
    }
    
    m_tracker->saveData();
}

void ConsoleUI::showMainMenu() {
    std::cout << "\n1. Show habits\n2. Create habit\n3. Mark completed\n4. Statistics\n5. Exit\nChoice: ";
}

void ConsoleUI::handleUserInput(int choice) {
    switch(choice) {
        case 1: displayAllHabits(); break;
        case 2: createHabitScreen(); break;
        case 3: markHabitScreen(); break;
        case 4: showStatisticsScreen(); break;
        case 5: m_isRunning = false; break;
        default: std::cout << "Invalid choice\n";
    }
}

void ConsoleUI::displayAllHabits() {
    std::cout << "Display habits - TODO\n";
}

void ConsoleUI::createHabitScreen() {
    std::cout << "Create habit - TODO\n";
}

void ConsoleUI::markHabitScreen() {
    std::cout << "Mark habit - TODO\n";
}

void ConsoleUI::showStatisticsScreen() {
    std::cout << "Statistics - TODO\n";
}

void ConsoleUI::showProgressBar(double percentage) {
}