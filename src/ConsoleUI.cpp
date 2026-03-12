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
                std::cout << "Invalid input, enter a number.\n";
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
        default: std::cout << "Invalid choice. Try again.\n";
    }
}

void ConsoleUI::displayAllHabits() {
    std::cout << "\n------------------------\n";
    std::cout << "    ALL YOUR HABITS     \n";
    std::cout << "------------------------\n";

    auto& habits = m_tracker->getHabits();

    if (habits.empty()) {
        std::cout << "No habits yet. Create one!\n";
    } else {
        for (const auto& habit : habits) {
            std::cout << "ID: " << habit->getId() << "\n";
            std::cout << "  Name: " << habit->getName() << "\n";
            std::cout << "  Type: " << habit->getType() << "\n";
            std::cout << "  Streak: " << habit->getStreak() << " days\n";

            if (habit->getType() == "numericHabit") {
                numericHabit* numHabit = dynamic_cast<numericHabit*>(habit.get());
                if (numHabit) {
                    auto progress = numHabit->getProgress();
                    if (progress.has_value()) {
                        std::cout << "  Progress: " << std::fixed << std::setprecision(1)
                                  << progress.value() << "%\n";
                    }
                    std::cout << "  Current: " << numHabit->getCurrentValue()
                              << " " << numHabit->getUnit() << "\n";
                    std::cout << "  Goal: " << numHabit->getGoal()
                              << " " << numHabit->getUnit() << "\n";
                }
            }

            auto last = habit->getLastEntry();
            if (last.has_value()) {
                std::cout << "  Last: " << (last.value() ? "done" : "not done") << "\n";
            } else {
                std::cout << "  Last: not marked yet\n";
            }

            double rate = habit->completionRate() * 100;
            std::cout << "  Overall: " << std::fixed << std::setprecision(1) << rate << "%\n";

            std::cout << "  ------------------------\n";
        }
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleUI::createHabitScreen() {
    std::cout << "\n------------------------\n";
    std::cout << "    CREATE NEW HABIT     \n";
    std::cout << "------------------------\n";

    std::string name;
    int typeChoice;
    double target = 1;
    std::string unit;

    std::cout << "Enter habit name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    if (name.empty()) {
        std::cout << "Habit name cannot be empty\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return;
    }

    std::cout << "\nHabit type:\n";
    std::cout << "  1. Boolean (done/not done)\n";
    std::cout << "  2. Numeric (with target value)\n";
    std::cout << "Choice: ";
    std::cin >> typeChoice;

    try {
        if (typeChoice == 1) {
            m_tracker->createHabit(name, HabitType::Boolean);
            std::cout << "Boolean habit created!\n";

        } else if (typeChoice == 2) {
            std::cout << "Enter target value: ";
            std::cin >> target;

            if (target <= 0) {
                std::cout << "Target must be positive\n";
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                return;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Enter unit (e.g., km, liters, pages): ";
            std::getline(std::cin, unit);

            m_tracker->createHabit(name, HabitType::Numeric, target, unit);
            std::cout << "Numeric habit '" << name << "' created successfully!\n";
            std::cout << "   Goal: " << target << " " << unit << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
void ConsoleUI::markHabitScreen() {
    std::cout << "\n------------------------\n";
    std::cout << "    MARK HABIT COMPLETED     \n";
    std::cout << "------------------------\n";

    int habitId;
    int value = 1;

    std::cout << "Enter habit ID: ";
    std::cin >> habitId;

    std::cout << "Enter value (for numeric habits): ";
    std::cin >> value;

    try {
        m_tracker->markHabitCompleted(habitId, value);
        std::cout << "Progress recorded\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleUI::showStatisticsScreen() {
    std::cout << "\n------------------------\n";
    std::cout << "       STATISTICS        \n";
    std::cout << "------------------------\n";

    auto& habits = m_tracker->getHabits();

    if (habits.empty()) {
        std::cout << "No habits yet. Create one first.\n";
    } else {
        std::cout << "\nYour habits:\n";
        for (const auto& habit : habits) {
            std::cout << "  ID " << habit->getId() << ": " << habit->getName()
                      << " (" << habit->getType() << ")\n";
        }

        std::cout << "\nEnter habit ID: ";
        int habitId;
        std::cin >> habitId;

        bool found = false;
        for (const auto& habit : habits) {
            if (habit->getId() == habitId) {
                found = true;

                int streak = m_tracker->getCurrentStreak(habitId);
                double rate = m_tracker->getCompletionRate(habitId, 7);

                std::cout << "\nStatistics for: " << habit->getName() << "\n";
                std::cout << "Current streak: " << streak << " days\n";
                std::cout << "Completion rate (7 days): " << std::fixed
                          << std::setprecision(1) << rate << "%\n";

                showProgressBar(rate);

                std::cout << "\nLast 7 days: ";
                const auto& history = habit->getHistory();
                int start = history.size() > 7 ? history.size() - 7 : 0;
                for (size_t i = start; i < history.size(); ++i) {
                    std::cout << (history[i] ? "1 " : "0 ");
                }
                std::cout << "\n";

                break;
            }
        }

        if (!found) {
            std::cout << "Habit with ID " << habitId << " not found.\n";
        }
    }

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