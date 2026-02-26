#include <iostream>
#include <memory>
#include "tracker.h"
#include "boolean_habit.h"
int main() {
    std::cout << "Test HabitTracker\n";
    habittracker tracker;

    auto habit = std::make_unique<BooleanHabit>("Exercise");
    std::cout << "Create a habit: Exercise\n";

    tracker.addHabit(std::move(habit));
    std::cout << "Add to tracker\n";

    std::cout << "Quantity of habits: " << tracker.size() << "\n";

    auto* found = tracker.findHabit("Exercise");
    if (found) {
        std::cout << "Found a habit: " << found->getName() << "\n";
    }

    bool marked = tracker.markHabitDone("Exercise", "2026-02-27");
    std::cout << "Noted the completion: " << (marked ? "seccessefully" : "mistake") << "\n";

    bool removed = tracker.removeHabit("Exercise");
    std::cout << "Removing a habit: " << (removed ? "seccessefully" : "mistake") << "\n";
    std::cout << "Quantity after removal: " << tracker.size() << "\n";

    return 0;
}