#pragma once
#include <string>

class Player {
public:
    explicit Player(const std::string& name);

    void recordAttendance(const std::string& dayOfWeek);

    void addPoints(int points);
    void setGrade(const std::string& grade);

    std::string getName() const;
    int getPoints() const;
    std::string getGrade() const;
    int getWednesdayCount() const;
    int getWeekendCount() const;

    bool isRemovalCandidate() const;

private:
    std::string name_;
    int points_ = 0;
    std::string grade_ = "Normal";
    int wednesdayCount_ = 0;
    int weekendCount_ = 0;
};