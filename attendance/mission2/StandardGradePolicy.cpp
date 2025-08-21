#include "StandardGradePolicy.h"

void StandardGradePolicy::apply(Player& player) {
    int points = player.getPoints();
    if (points >= 50) {
        player.setGrade("Gold");
    }
    else if (points >= 30) {
        player.setGrade("Silver");
    }
    else {
        player.setGrade("Normal");
    }
}