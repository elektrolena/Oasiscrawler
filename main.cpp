#include <iostream>
#include <ctime> // for random seed
#include <iomanip>
#include <string>
#include "character.h"
#include "monster.h"
#include "world.h"

int main()
{
    char start;
    srand(time(0)); // initialize random seed
    Character character;
    Monster monster;
    World world;

    world.instruction(character);
    world.generateWorld();

    // game loop
    while (!world.isGameOver(character)) //while player has lifepoints left
    {
        char direction;
        system("cls");
        character.printStats();   // print player stats
        world.display(character, monster); // display the world

        std::cin >> direction;

        if(world.isExit(direction)) // if the player wants to exit
        {
            return 0;
        }

        while(!character.movechar(direction, world.getFieldSize())) //if the player gives a wrong input or is at the boarder of the field
        {
            if(world.isExit(direction)) //if the player exits the game
            {
                return 0;
            }
            std::cin >> direction;
        }
        monster.moveMonster(character, world.getFieldSize()); //monster takes a step
        world.steppedOnField(character, monster); //stepped on field gets activated

        if (world.isGameWon(character) && character.getLevel() < 10) //if the current level is completed
        {
            system("cls");
            world.increaseFieldSize(); //increase the size of the world
            character.increaseLevel(); //increase the level of the character
            std::cin >> start;
            world.generateWorld(); //generate a new world
        }
        else if(world.isGameWon(character) && character.getLevel() == 10) //if the last level is completed
        {
            system("cls");
            std::cout << std::setfill('*') << std::setw(100) << "" << std::endl; //fills line with stars
            std::cout << std::setfill(' ') << std::setw(35) << "" << "YOU WON" << std::endl; //prints text in the middle
            std::cout << std::setfill('*') << std::setw(100) << "" << std::endl;
            std::cout << std::endl;
            std::cout << "Thank you for playing." << std::endl;
            break;
        }
    }
    system("cls");
    std::cout << std::setfill('*') << std::setw(100) << "" << std::endl; //fills line with stars
    std::cout << std::setfill(' ') << std::setw(35) << "" << "GAME OVER" << std::endl; //prints text in the middle
    std::cout << std::setfill('*') << std::setw(100) << "" << std::endl;
    character.printHistory(); //prints the game history
    return 0;
}
