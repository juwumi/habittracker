#include <gtest/gtest.h>
#include "../include/habit.h"
#include "../include/booleanHabit.h"
#include "../include/numericHabit.h"

// тесты для habit
TEST(HabitTest, UniqueID) {
    booleanHabit habit1("1st");
    booleanHabit habit2("2nd");

    EXPECT_NE(habit1.getId(),habit2.getId());
}

TEST(HabitTest, EmptyNameNotWorks) {
    EXPECT_THROW( booleanHabit habit(""), HabitException);
}

TEST(HabitTest,InvalidTargetDaysNotWorks) {
    EXPECT_THROW(booleanHabit habit("test",0), HabitException);

    EXPECT_THROW(booleanHabit habit("test",-1), HabitException);
}

//тесты для booleanHabit

TEST(BooleanHabitTest, Creation) {
    booleanHabit habit("Reading", 3);

    EXPECT_EQ(habit.getName(),"Reading");
    EXPECT_EQ(habit.getTargetDaysPerWeek(),3);
    EXPECT_EQ(habit.getType(),"booleanHabit");
    EXPECT_TRUE(habit.getGoal());
}

TEST(BooleanHabitTest,MarkAndStreak) {
    booleanHabit habit("Reading");
    habit.markCompleted(true);
    habit.markCompleted(true);
    habit.markCompleted(true);
    habit.markCompleted(false);

    EXPECT_EQ(habit.getHistory().size(),4);
    EXPECT_EQ(habit.getStreak(),0);
}

TEST(BooleanHabitTest, GoalSetter) {
    booleanHabit habit("Meditation");

    EXPECT_TRUE(habit.getGoal());
    habit.setGoal(false);
    EXPECT_FALSE(habit.getGoal());
}

//тесты для numericHabit
TEST(NumericHabitTest,Creation) {
    numericHabit habit("Number of steps",8000,"steps",7 );

    EXPECT_EQ(habit.getName(),"Number of steps");
    EXPECT_DOUBLE_EQ(habit.getGoal(),8000);
    EXPECT_EQ(habit.getUnit(),"steps");
    EXPECT_EQ(habit.getTargetDaysPerWeek(),7);
}

TEST(NumericHabitTest, WaterProgress) {
    numericHabit habit("Water", 2.5, "liters");

    habit.setValue(1.0);
    EXPECT_DOUBLE_EQ(habit.getProgress().value(), 40.0);
}

TEST(NumericHabitTest, ReadingGoal) {
    numericHabit habit("Read book", 50, "pages", 5);

    EXPECT_EQ(habit.getTargetDaysPerWeek(), 5);
    habit.setValue(50);
    EXPECT_TRUE(habit.isGoalReached());
}

TEST(NumericHabitTest, ZeroGoal) {
    numericHabit habit("Something", 0, "units");
    EXPECT_FALSE(habit.getProgress().has_value());
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}