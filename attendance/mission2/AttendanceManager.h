#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Player.h"
#include "IGradePolicy.h"

class AttendanceManager {
public:
    AttendanceManager(const std::shared_ptr<IGradePolicy>& gradePolicy);

    void processAttendanceFile(const std::string& filename);
    void calculateResults();

    std::vector<Player> getPlayers() const;
    std::vector<Player> getRemovalCandidates() const;

private:
    std::vector<Player> players_;

    // IPointPolicy ��� ���� ����
    std::shared_ptr<IGradePolicy> gradePolicy_;

    Player* findPlayerByName(const std::string& name);
};