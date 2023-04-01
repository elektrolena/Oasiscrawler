#ifndef WORLD_H
#define WORLD_H

#include "monster.h"

class World
{
private:
    int x;
    int y;
    int grid[25][25];
    int fieldsize;
    int numRelics;

public:
    World();
    void setFieldSize();
    int getFieldSize();
    void generateWorld();
    void instruction(Character& character);
    void display(Character& character, Monster& monster);
    void steppedOnField(Character& character, Monster& monster);
    void increaseFieldSize();
    bool isGameOver(Character& character);
    bool isGameWon(Character& character);
    bool isExit(char direction);
};

#endif // WORLD_H
