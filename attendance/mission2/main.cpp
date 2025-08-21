#ifdef _DEBUG

#include "gmock/gmock.h"

int main() {
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <iostream>
#include <vector>
#include <memory>
#include "AttendanceManager.h"
#include "StandardGradePolicy.h"

void printResults(const AttendanceManager& manager) {
    for (const auto& player : manager.getPlayers()) {
        std::cout << "NAME : " << player.getName() << ", ";
        std::cout << "POINT : " << player.getPoints() << ", ";
        std::cout << "GRADE : " << player.getGrade() << "\n";
    }
}

void printRemovedPlayers(const AttendanceManager& manager) {
    std::cout << "\nRemoved player\n";
    std::cout << "==============\n";
    for (const auto& candidate : manager.getRemovalCandidates()) {
        std::cout << candidate.getName() << "\n";
    }
}

int main() {
    std::shared_ptr<IGradePolicy> gradePolicy = std::make_shared<StandardGradePolicy>();
    AttendanceManager manager(gradePolicy);

    manager.processAttendanceFile("attendance_weekday_500.txt");
    manager.calculateResults();

    printResults(manager);
    printRemovedPlayers(manager);

    return 0;
}

#endif