#ifndef STATISTICS_H
#define STATISTICS_H

#include "Types.h"
#include <vector>
#include <map>
#include <chrono>

class Statistics {
public:
    Statistics() = default;
    
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
};

#endif