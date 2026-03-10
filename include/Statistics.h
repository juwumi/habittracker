#ifndef STATISTICS_H
#define STATISTICS_H

#include "Types.h"
#include <map>
#include <vector>
#include <chrono>

using LogMap = std::map<std::chrono::system_clock::time_point, std::vector<DailyProgress>>;

class Statistics {
public:
    Statistics() = default;
    
    constexpr static double getWeight(char channel) {
        switch(channel) {
            case 'D': return 1.0;
            default: return 0.0;
        }
    }
    
    int calculateStreak(int habitId, const LogMap& logs) const;
    
    double calculateCompletionRate(int habitId, int days, const LogMap& logs) const;
};

#endif