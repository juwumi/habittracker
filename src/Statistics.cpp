#include "Statistics.h"
#include <iostream> 

Statistics::Statistics() {
    counter = std::make_shared<int>(0);
    std::cout << "Statistics created with counter\n";
}

int Statistics::calculateStreak(int habitId, 
    const std::map<std::chrono::system_clock::time_point, std::vector<DailyProgress>>& logs) const {
    return 0;
}

double Statistics::calculateCompletionRate(int habitId, int days, 
    const std::map<std::chrono::system_clock::time_point, std::vector<DailyProgress>>& logs) const {
    return 0.0;
}

void Statistics::incrementCounter() {
    (*counter)++;
    std::cout << "Statistics counter: " << *counter << std::endl;
}