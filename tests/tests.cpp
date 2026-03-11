#include <gtest/gtest.h>
#include <filesystem>
#include "../include/habit.h"
#include "../include/booleanHabit.h"
#include "../include/numericHabit.h"
#include "../include/dailylog.h"
#include "../include/storage.h"
#include "../include/logmanager.h"

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

//тесты для dailylog

TEST(DailyLogTest, Constructor) {
    DailyLog log("2026-03-10");
    EXPECT_EQ(log.getDate(), "2026-03-10");
}

TEST(DailyLogTest, AddAndGetBooleanEntry) {
    DailyLog log("2026-03-10");

    log.addEntry(1, true);

    auto entry = log.getEntry(1);
    ASSERT_TRUE(entry.has_value());
    ASSERT_TRUE(std::holds_alternative<bool>(entry.value()));
    EXPECT_TRUE(std::get<bool>(entry.value()));
}

TEST(DailyLogTest, AddAndGetNumericEntry) {
    DailyLog log("2026-03-10");

    log.addEntry(2, 5000);

    auto entry = log.getEntry(2);
    ASSERT_TRUE(entry.has_value());
    ASSERT_TRUE(std::holds_alternative<int>(entry.value()));
    EXPECT_EQ(std::get<int>(entry.value()), 5000);
}

TEST(DailyLogTest, GetNonexistentEntry) {
    DailyLog log("2026-03-10");

    auto entry = log.getEntry(999);
    EXPECT_FALSE(entry.has_value());
}

TEST(DailyLogTest, HasEntry) {
    DailyLog log("2026-03-10");

    log.addEntry(1, true);

    EXPECT_TRUE(log.hasEntry(1));
    EXPECT_FALSE(log.hasEntry(2));
}

TEST(DailyLogTest, GetAllEntries) {
    DailyLog log("2026-03-10");

    log.addEntry(1, true);
    log.addEntry(2, 5000);

    const auto& entries = log.getAllEntries();
    EXPECT_EQ(entries.size(), 2);
}

TEST(DailyLogTest, SerializeDeserialize) {
    DailyLog log("2026-03-10");
    log.addEntry(1, true);
    log.addEntry(2, 5000);

    std::string serialized = log.serialize();

    auto restored = DailyLog::deserialize(serialized);

    EXPECT_EQ(restored->getDate(), "2026-03-10");

    auto entry1 = restored->getEntry(1);
    ASSERT_TRUE(entry1.has_value());
    ASSERT_TRUE(std::holds_alternative<bool>(entry1.value()));
    EXPECT_TRUE(std::get<bool>(entry1.value()));

    auto entry2 = restored->getEntry(2);
    ASSERT_TRUE(entry2.has_value());
    ASSERT_TRUE(std::holds_alternative<int>(entry2.value()));
    EXPECT_EQ(std::get<int>(entry2.value()), 5000);
}

//тесты для storage

class StorageTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::remove("test_storage.txt");
    }

    void TearDown() override {
        std::filesystem::remove("test_storage.txt");
    }
};

TEST_F(StorageTest, SaveAndLoadLogs) {
    Storage storage("test_storage.txt");

    std::vector<std::unique_ptr<DailyLog>> logs;

    auto log1 = std::make_unique<DailyLog>("2026-03-10");
    log1->addEntry(1, true);
    logs.push_back(std::move(log1));

    auto log2 = std::make_unique<DailyLog>("2026-03-11");
    log2->addEntry(2, 5000);
    logs.push_back(std::move(log2));

    EXPECT_NO_THROW(storage.saveLogs(logs));

    auto loaded = storage.loadLogs();
    ASSERT_TRUE(loaded.has_value());
    ASSERT_EQ(loaded->size(), 2);

    EXPECT_EQ((*loaded)[0]->getDate(), "2026-03-10");
    EXPECT_EQ((*loaded)[1]->getDate(), "2026-03-11");
}

TEST_F(StorageTest, LoadFromNonexistentFile) {
    Storage storage("nonexistent.txt");

    auto loaded = storage.loadLogs();
    EXPECT_FALSE(loaded.has_value());
}

TEST_F(StorageTest, SaveEmptyLogs) {
    Storage storage("test_storage.txt");

    std::vector<std::unique_ptr<DailyLog>> emptyLogs;
    EXPECT_NO_THROW(storage.saveLogs(emptyLogs));

    auto loaded = storage.loadLogs();
    ASSERT_TRUE(loaded.has_value());
    EXPECT_TRUE(loaded->empty());
}

//тесты для numericHabit logmanager

class LogManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::remove("test_manager.txt");
        storage = std::make_unique<Storage>("test_manager.txt");
        logManager = std::make_unique<LogManager>(*storage);
    }

    void TearDown() override {
        std::filesystem::remove("test_manager.txt");
    }

    std::unique_ptr<Storage> storage;
    std::unique_ptr<LogManager> logManager;
};

TEST_F(LogManagerTest, MarkDoneToday) {
    logManager->markDone(1, true);

    auto value = logManager->getTodayValue(1);
    ASSERT_TRUE(value.has_value());
    ASSERT_TRUE(std::holds_alternative<bool>(value.value()));
    EXPECT_TRUE(std::get<bool>(value.value()));
}

TEST_F(LogManagerTest, MarkDoneForDate) {
    logManager->markDoneForDate(1, "2026-03-09", 5000); 

    auto value = logManager->getValueForDate(1, "2026-03-09");
    ASSERT_TRUE(value.has_value());
    ASSERT_TRUE(std::holds_alternative<int>(value.value()));
    EXPECT_EQ(std::get<int>(value.value()), 5000);
}

TEST_F(LogManagerTest, GetLog) {
    logManager->markDone(1, true);

    std::string today = logManager->getTodayDate();
    auto log = logManager->getLog(today);

    ASSERT_TRUE(log.has_value());
    EXPECT_EQ(log.value()->getDate(), today);
}

TEST_F(LogManagerTest, GetNonexistentLog) {
    auto log = logManager->getLog("2099-01-01");
    EXPECT_FALSE(log.has_value());
}

TEST_F(LogManagerTest, IsHabitDoneToday) {
    logManager->markDone(1, true);
    logManager->markDone(2, false);

    EXPECT_TRUE(logManager->isHabitDoneToday(1));
    EXPECT_FALSE(logManager->isHabitDoneToday(2));
}

TEST_F(LogManagerTest, GetLogsInRange) {
    logManager->markDoneForDate(1, "2026-03-08", true);
    logManager->markDoneForDate(1, "2026-03-09", true);
    logManager->markDoneForDate(1, "2026-03-10", true);

    auto range = logManager->getLogsInRange("2026-03-08", "2026-03-09");

    EXPECT_EQ(range.size(), 2);
}

TEST_F(LogManagerTest, CountCompletions) {
    logManager->markDoneForDate(1, "2026-03-08", true);
    logManager->markDoneForDate(1, "2026-03-09", true);
    logManager->markDoneForDate(1, "2026-03-10", false);

    int count = logManager->countCompletionsInRange(1, "2026-03-08", "2026-03-10");

    EXPECT_EQ(count, 2);
}

TEST_F(LogManagerTest, AutoSave) {
    logManager->markDone(1, true);

    LogManager newManager(*storage);

    auto value = newManager.getTodayValue(1);
    ASSERT_TRUE(value.has_value());
    EXPECT_TRUE(std::get<bool>(value.value()));
}

TEST_F(LogManagerTest, Clear) {
    logManager->markDone(1, true);

    EXPECT_FALSE(logManager->getAllLogs().empty());

    logManager->clear();
    EXPECT_TRUE(logManager->getAllLogs().empty());
}

TEST_F(LogManagerTest, GetAllLogs) {
    logManager->markDone(1, true);
    logManager->markDoneForDate(1, "2026-03-09", true);

    const auto& allLogs = logManager->getAllLogs();
    EXPECT_GE(allLogs.size(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}