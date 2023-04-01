#include <iostream>
#include <cstdlib>
#include "monster.h"

Monster::Monster() //constructor
{
    x = rand()%3+2;
    y = rand()%3+2;
}

int Monster::getX() //returns x coordinate
{
    return x;
}

int Monster::getY() //returns y coordinate
{
    return y;
}

void Monster::moveMonster(Character& character, int boarder) //monster moves when the player is in the same row or column
{
    if(character.getX() == x) //same row?
    {
        if(character.getY() < y && y > 0)
        {
            y--;
        }
        else if(character.getY() > y && y < boarder)
        {
            y++;
        }
    }
    else if(character.getY() == y) //same column?
    {
        if(character.getX() < x && x > 0)
        {
            x--;
        }
        else if(character.getX() > x && x < boarder)
        {
            x++;
        }
    }
}
