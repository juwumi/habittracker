#ifndef STATISTICS_H
#define STATISTICS_H

#include "Types.h"
#include <map>
#include <vector>
#include <chrono>
#include <memory>

class Statistics {
public:
    Statistics();
    
    constexpr static double getWeight(char channel) {
        switch(channel) {
            case 'D': return 1.0;
            default: return 0.0;
        }
    }
    
    int calculateStreak(int habitId, 
        const std::map<std::chrono::system_clock::time_point, std::vector<DailyProgress>>& logs) const;
    
    double calculateCompletionRate(int habitId, int days, 
        const std::map<std::chrono::system_clock::time_point, std::vector<DailyProgress>>& logs) const;
    
    void incrementCounter();

private:
    std::shared_ptr<int> counter;
};

#endif