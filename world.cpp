#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "world.h"

World::World() //constructor
{
    x = 0;
    y = 0;
}

void World::instruction(Character& character) //instruction
{
    char start;

    std::cout << std::setfill('*') << std::setw(100) << "" << std::endl; //fills line with stars
    std::cout << std::setfill(' ') << std::setw(35) << "" << "WELCOME TO OASISCRAWLER" << std::endl; //prints text in the middle
    std::cout << std::setfill('*') << std::setw(100) << "" << std::endl;
    std::cout << "\nYou (P) landed in a world full of danger and monsters. To get out, you have to find all relics (*)." << std::endl;
    std::cout << "\nThere are 10 levels. With each level, the field gets bigger and the number of dangerfields increases." << std::endl;
    std::cout << "\nAt the beginning, you have 1 invisibility potion, 1 flying potion and 1 potion to breathe underwater." << std::endl;
    std::cout << "When encountering a danger other than the monster, you can use them to escape." << std::endl;
    std::cout << "\nThe monster (M) can only see you if you are in the same row or column." << std::endl;
    std::cout << "As soon as it spots you, it takes a step towards you." << std::endl;
    std::cout << "Don't let it catch you, it will kill you, no matter how many lives you have left." << std::endl;
    std::cout << "\nBefore we start, you can decide how big the world should be (5x5 - 10x10)." << std::endl;
    std::cout << "(Please note that the bigger the field is, the more difficult it is to complete each level.)" << std::endl;
    std::cout << "To do so, please enter a number from 5 to 10." << std::endl;
    setFieldSize(); //lets player decide field size
    std::cout << "Next up, you can choose how many lives you want to start with. (Minimum: 3, Maximum: 10)" << std::endl;
    std::cout << "(Please note that the more lives you have at the beginning, the easier the game will be.)" << std::endl;
    character.setLifePoints(); //lets player decide lifepoints
    std::cout << "Great! Now press any key to start. And watch out for the monsters." << std::endl;
    std::cin >> start;
    character.addToHistory("\n\nLEVEL 1:"); //adds to history
}

void World::setFieldSize() //lets player decide field size
{
    int temp = 0;
    while(temp < 5 || temp > 10)
    {
        std::cin >> temp;
        std::cin.clear();
        std::cin.ignore(2, '\n'); //prevents infinity loop when input is a char
        if(temp >= 5 && temp <= 10)
        {
            fieldsize = temp;
            break;
        }
        else
        {
            std::cout << "Invalid number! Try again." << std::endl;
        }
    }
}

int World::getFieldSize() //returns size of the world
{
    return fieldsize;
}

void World::generateWorld() //generates the world
{
    numRelics = 0;
    for(int y = 0; y < fieldsize; y++)
    {
        for(int x = 0; x < fieldsize; x++)
        {
            grid[x][y] = rand()%10;
            if(grid[x][y] <= 3) //Für Zahlen 0-3 leeres Feld
            {
                grid[x][y] = 1; //empty
            }
            else if(grid[x][y] > 3 && grid[x][y] < 8) //für Zahlen 4-7 Gefahrenfeld
            {
                grid[x][y] = 6; //danger
            }
            else if(grid[x][y] == 8) //für Zahl 8 Brunnenfeld
            {
                grid[x][y] = 3; //fountain
            }
            else if(grid[x][y] == 9 && x != 0 && y != 0) //für Zahl 9 Reliktfeld
            {
                grid[x][y] = 7; //relic
                numRelics++;
            }
        }
    }
    grid[0][0] = 1;
    // Make sure there is at least one relic in the game world
    if(numRelics == 0)
    {
        grid[rand()%fieldsize][rand()%fieldsize] = 7;
        numRelics++;
    }
}

void World::display(Character& character, Monster& monster) //prints the world with the player, monster and relics
{
    for(int y = 0; y < fieldsize; y++)
    {
        std::cout << std::setfill('-') << std::setw(fieldsize * 4 + 1) << "" << std::endl;
        for(int x = 0; x < fieldsize; x++)
        {
            if(character.getX() == x && character.getY() == y)
            {
                std::cout << "| P ";
            }
            else if(monster.getX() == x && monster.getY() == y)
            {
                std::cout << "| M ";
            }
            else if(grid[x][y] == 7)
            {
                std::cout << "| * ";
            }
            else
            {
                std::cout << "|   ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::setfill('-') << std::setw(fieldsize * 4 + 1) << "" << std::endl;
    std::cout << std::setfill('_') << std::setw(70) << "" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter a direction (w = up/a = left/s = down/d = right). Click (x) to exit the game: ";
}

void World::steppedOnField(Character& character, Monster& monster) //checks the kind of field the player has stepped on
{
    int currentfield = 0;
    int danger = 0;
    currentfield = grid[character.getX()][character.getY()];
    if(character.getX() == monster.getX() && character.getY() == monster.getY()) //when the monster caught the player
    {
        character.die();
    }
    else if(currentfield == 7) //relic
    {
        character.increaseRelicPoints(); //increase players relic points
        numRelics--; //decreases number of total relics
    }
    else if(currentfield == 3) //fountainfield
    {
        character.actionFountainField();
    }
    else if(currentfield == 6) //dangerfield
    {
        if(character.getLevel() < 3)
        {
            danger = rand()%8; //probability of crucial dangerfields depending on the current level
            character.actionDangerField(danger);
        }
        else if(character.getLevel() < 5)
        {
            danger = rand()%7;
            character.actionDangerField(danger);
        }
        else if(character.getLevel() < 7)
        {
            danger = rand()%6;
            character.actionDangerField(danger);
        }
        else if(character.getLevel() < 9)
        {
            danger = rand()%5;
            character.actionDangerField(danger);
        }
        else
        {
            danger = rand()%4;
            character.actionDangerField(danger);
        }
    }
    grid[character.getX()][character.getY()] = 1; //sets field to empty field after the dangerfield process is over
}

void World::increaseFieldSize() //increases worldsize after finishing a level
{
    fieldsize++;
}

bool World::isGameOver(Character& character) //returns true when the player has no lifepoints left
{
    if(character.getLifePoints() == 0)
        return true;
    else
        return false;
}

bool World::isGameWon(Character& character) //returns true when all relics were found
{
    if(numRelics == 0)
        return true;
    else
        return false;
}

bool World::isExit(char direction) //returns true if the player exits the game
{
    if(direction == 'x')
    {
        std::cout << "You've exited the game. Thank you for playing." << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}
