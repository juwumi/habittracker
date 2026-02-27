#indef HABIT_H
#endif HABIT_H

#include <string>
#include<vector>

class Habit{
protected:
    std::string name;
    int streak;
    std::vector<bool> history;
public:
    explicit Habit(std::string name);
    virtual ~Habit();
    virtual std::string getType() const = 0;

    void markCompleted();
    void updateStreak();
    double completionRate() const;

    std::string getName() const { return name; }
    int getStreak() const { return streak; }
    const std::vector<bool>& getHistory() const { return history; }

    virtual std::string toString() const = 0;
    virtual void print() const = 0;
};
#endif
