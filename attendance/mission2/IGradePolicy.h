#pragma once
#include "Player.h" // Player�� ���¸� �����ؾ� �ϹǷ� ����

class IGradePolicy {
public:
    // ��� ��� ��å�� Player�� �޾� ����� �ű�� apply �Լ��� �ݵ�� ������ ��
    virtual void apply(Player& player) = 0;
    virtual ~IGradePolicy() = default;
};