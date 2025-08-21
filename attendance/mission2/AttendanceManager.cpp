#include "AttendanceManager.h"
#include <fstream>
#include <algorithm>

AttendanceManager::AttendanceManager(const std::shared_ptr<IGradePolicy>& gradePolicy)
    : gradePolicy_(gradePolicy) {
}

void AttendanceManager::processAttendanceFile(const std::string& filename) {
    std::ifstream fin(filename);
    std::string name, dayOfWeek;
    while (fin >> name >> dayOfWeek) {
        Player* player = findPlayerByName(name);

        if (player == nullptr) {
            players_.emplace_back(name);
            player = &players_.back();
        }

        player->recordAttendance(dayOfWeek);
    }
}

Player* AttendanceManager::findPlayerByName(const std::string& name) {
    for (Player& player : players_) {
        if (player.getName() == name) {
            return &player;
        }
    }
    return nullptr;
}

void AttendanceManager::calculateResults() {
    for (Player& player : players_) {
        if (player.getWednesdayCount() >= 10) {
            player.addPoints(10);
        }
        if (player.getWeekendCount() >= 10) {
            player.addPoints(10);
        }

        gradePolicy_->apply(player);
    }
}

std::vector<Player> AttendanceManager::getPlayers() const {
    return players_;
}

std::vector<Player> AttendanceManager::getRemovalCandidates() const {
    std::vector<Player> candidates;
    for (const Player& player : players_) {
        if (player.isRemovalCandidate()) {
            candidates.push_back(player);
        }
    }
    return candidates;
}