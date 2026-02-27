#include "habit.h"

#include <algorithm>
#include <numeric>

Habit::Habit(std::string name): name(std::move(name)), streak(0){}
Habit::~Habit(){}

void Habit::makeCompleted(){
    history.push_back(true);
    updateStreak();
}

void Habit::updateStreak(){
    streak=0;
    for(int i=history.size()-1; i>=0; i--){
        if(history[i]){
            streak++;
        } else{
            break;
        }
    }
}

double Habit::completionRate() const{
    if(history.empty()) return 0.0;
    int completed=0;
    for(bool day: history){
        if(day) completed++;
    }
    return (static_cast<double>(completed)/history.size())*100.0;
}