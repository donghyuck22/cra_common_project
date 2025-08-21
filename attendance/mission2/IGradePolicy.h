#pragma once
#include "Player.h" // Player의 상태를 변경해야 하므로 포함

class IGradePolicy {
public:
    // 모든 등급 정책은 Player를 받아 등급을 매기는 apply 함수를 반드시 가져야 함
    virtual void apply(Player& player) = 0;
    virtual ~IGradePolicy() = default;
};