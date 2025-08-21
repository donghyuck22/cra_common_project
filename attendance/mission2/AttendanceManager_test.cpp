#include "gmock/gmock.h"
#include <fstream>
#include <memory>
#include "AttendanceManager.h"
#include "StandardGradePolicy.h"

void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

TEST(PlayerTest, checkRecodedPointWithDefault) {
    Player player("Nina");
    player.recordAttendance("monday");  
    EXPECT_EQ(player.getPoints(), 1);
}

TEST(PlayerTest, checkRecodedPointWithWednesday) {
    Player player("Nina");
    player.recordAttendance("wednesday");
    EXPECT_EQ(player.getPoints(), 3);
}

TEST(PlayerTest, checkRecodedPointWithSaturday) {
    Player player("Nina");
    player.recordAttendance("saturday"); 
    EXPECT_EQ(player.getPoints(), 2);
}

TEST(PlayerTest, checkWednesdayCount) {
    Player player("Nina");
    player.recordAttendance("wednesday");   
    EXPECT_EQ(player.getWednesdayCount(), 1);
}

TEST(PlayerTest, checkWeekendCount) {
    Player player("Nina");
    player.recordAttendance("saturday");   
    EXPECT_EQ(player.getWeekendCount(), 1);
}

TEST(PlayerTest, IsRemovalCandidateWithNormal) {
    Player candidate("candidate");
    EXPECT_TRUE(candidate.isRemovalCandidate());
}

TEST(PlayerTest, isNotRemovealCandidateWithWednesday) {
    Player candidate("candidate");
    EXPECT_TRUE(candidate.isRemovalCandidate());
}

TEST(PlayerTest, isNotRemovealCandidateWithSilver) {
    Player candidate("candidate"); 
    EXPECT_TRUE(candidate.isRemovalCandidate());
}

class AttendanceManagerTest : public ::testing::Test {
protected:
    std::shared_ptr<IGradePolicy> gradePolicy;

    void SetUp() override {
        gradePolicy = std::make_shared<StandardGradePolicy>();
    }
};

TEST_F(AttendanceManagerTest, GetWednesdayBonusCount) {
    std::string content;
    for (int i = 0; i < 20; ++i) content += "Alice wednesday\n";
    createTestFile("test.txt", content);
    
    AttendanceManager manager(gradePolicy);
    manager.processAttendanceFile("test.txt");
    manager.calculateResults();

    auto players = manager.getPlayers();
    for (const auto& p : players) {
        if (p.getName() == "Alice") {
            EXPECT_EQ(p.getPoints(), 70);
            EXPECT_EQ(p.getGrade(), "Gold");
        }
    }
}

TEST_F(AttendanceManagerTest, GetWeekendBonusCount) {
    std::string content;
    for (int i = 0; i < 20; ++i) content += "Alice saturday\n";
    createTestFile("test.txt", content);

    AttendanceManager manager(gradePolicy);
    manager.processAttendanceFile("test.txt");
    manager.calculateResults();

    auto players = manager.getPlayers();
    for (const auto& p : players) {
        if (p.getName() == "Alice") {
            EXPECT_EQ(p.getPoints(), 50);
            EXPECT_EQ(p.getGrade(), "Gold");
        }
    }
}

TEST_F(AttendanceManagerTest, HandlesEmptyFile) {
    createTestFile("empty.txt", "");
    AttendanceManager manager(gradePolicy);
    manager.processAttendanceFile("empty.txt");
    manager.calculateResults();

    EXPECT_TRUE(manager.getPlayers().empty());
    EXPECT_TRUE(manager.getRemovalCandidates().empty());
}

TEST_F(AttendanceManagerTest, getPlayersNumber) {
    createTestFile("test.txt", "Alice monday\nBob tuesday\nAlice wednesday\n");
    AttendanceManager manager(gradePolicy);
    manager.processAttendanceFile("test.txt");

    auto players = manager.getPlayers();
    ASSERT_EQ(players.size(), 2);
}

TEST_F(AttendanceManagerTest, AppliesBonusesAndGradesCorrectly) {
    std::string content;
    for (int i = 0; i < 10; ++i) content += "Alice wednesday\n"; 
    for (int i = 0; i < 9; ++i) content += "Bob saturday\n";
    createTestFile("test.txt", content);

    AttendanceManager manager(gradePolicy);
    manager.processAttendanceFile("test.txt");
    manager.calculateResults();

    auto players = manager.getPlayers();
    for (const auto& p : players) {
        if (p.getName() == "Alice") {
            EXPECT_EQ(p.getPoints(), 40);
            EXPECT_EQ(p.getGrade(), "Silver");
        }
        else if (p.getName() == "Bob") {
            EXPECT_EQ(p.getPoints(), 18);
            EXPECT_EQ(p.getGrade(), "Normal");
        }
    }
}

TEST_F(AttendanceManagerTest, IdentifiesAndExcludesRemovalCandidates) {
    createTestFile("test.txt", "RemovedName monday\nNotRemovedName wednesday\n");
    AttendanceManager manager(gradePolicy);
    manager.processAttendanceFile("test.txt");
    manager.calculateResults();

    auto candidates = manager.getRemovalCandidates();
    ASSERT_EQ(candidates.size(), 1);
    EXPECT_EQ(candidates[0].getName(), "RemovedName");
}