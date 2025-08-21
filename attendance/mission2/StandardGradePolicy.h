#pragma once
#include "IGradePolicy.h"

class StandardGradePolicy : public IGradePolicy {
public:
    void apply(Player& player) override;
};