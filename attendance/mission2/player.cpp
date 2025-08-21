#include "Player.h"

Player::Player(const std::string& name) : name_(name) {}

void Player::recordAttendance(const std::string& dayOfWeek) {
    if (dayOfWeek == "wednesday") {
        points_ += 3;
        wednesdayCount_++;
    }
    else if (dayOfWeek == "saturday" || dayOfWeek == "sunday") {
        points_ += 2;
        weekendCount_++;
    }
    else {
        points_ += 1;
    }
}

void Player::addPoints(int points) {
    points_ += points;
}

void Player::setGrade(const std::string& grade) {
    grade_ = grade;
}

std::string Player::getName() const {
    return name_;
}

int Player::getPoints() const {
    return points_;
}

std::string Player::getGrade() const {
    return grade_;
}

int Player::getWednesdayCount() const {
    return wednesdayCount_;
}

int Player::getWeekendCount() const {
    return weekendCount_;
}

bool Player::isRemovalCandidate() const {
    return (grade_ == "Normal" && wednesdayCount_ == 0 && weekendCount_ == 0);
}