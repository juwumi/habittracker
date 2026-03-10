#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "HabitTracker.h"
#include <memory>

class ConsoleUI {
public:
    explicit ConsoleUI(std::unique_ptr<HabitTracker> tracker);
    void run();

private:
    void showMainMenu();
    void handleUserInput(int choice);
    void displayAllHabits();
    void createHabitScreen();
    void markHabitScreen();
    void showStatisticsScreen();
    void showProgressBar(double percentage);
    
    std::unique_ptr<HabitTracker> m_tracker;
    bool m_isRunning;
};

#endif