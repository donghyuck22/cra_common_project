#pragma once
#include "Player.h" 

class IGradePolicy {
public:
    virtual void apply(Player& player) = 0;
    virtual ~IGradePolicy() = default;
};
