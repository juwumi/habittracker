#include "habit.h"

habit::habit(const std::string& name, int targetDaysPerWeek): name(name), targetDaysPerWeek(targetDaysPerWeek) {
    if (name.length() == 0) {
        throw HabitException("Название привычки не может быть пустымy");
    }
}

void habit::markCompleted(bool done){
    history.push_back(done);
    updateStreak();
}

void habit::updateStreak(){
    streak=0;
    for(int i=history.size()-1; i>=0; i--){
        if(history[i]){
            streak++;
        } else{
            break;
        }
    }
}

double habit::completionRate() const{
    if(history.empty()) return 0.0;
    int completed=0;
    for(bool day: history){
        if(day) completed++;
    }
    return (static_cast<double>(completed)/history.size());
}
std::optional<bool> habit::getLastEntry() const {
    if (history.empty()) return std::nullopt;
    return history.back();
}
