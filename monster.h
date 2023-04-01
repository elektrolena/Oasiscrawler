#ifndef MONSTER_H
#define MONSTER_H

#include "character.h"

class Monster {
private:
    int x;
    int y;

public:
    Monster();
    int getX();
    int getY();
    void moveMonster(Character& character, int boarder);
};


#endif // MONSTER_H
