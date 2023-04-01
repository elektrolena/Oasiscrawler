#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

#include "character.h"

Character::Character() //constructor
{
    lifePoints = 5;
    relicPoints = 0;
    level = 1;
    x = 0;
    y = 0;
    step = 0; //variable to count every step
    invisibilityPotion = 1;
    flyingPotion = 1;
    breathingPotion = 1;
    history = "\nHISTORY:";
}

int Character::getLifePoints() //return current lifepoints
{
    if(lifePoints <= 0)
        return 0;
    else
        return lifePoints;
}

int Character::getLevel() //return current level
{
    return level;
}

int Character::getX() //return x coordinate
{
    return x;
}

int Character::getY() //return y coordinate
{
    return y;
}

void Character::setLifePoints() //let player choose lifepoints
{
    int temp = 0; //temporary variable to check if the input is possible
    while(temp < 3 || temp > 10)
    {
        std::cin >> temp;
        std::cin.clear();
        std::cin.ignore(2, '\n'); //prevents infinity prints when input is a char
        if(temp >= 3 && temp <= 10)
        {
            lifePoints = temp;
            break;
        }
        else
        {
            std::cout << "Invalid number! Try again." << std::endl;
        }
    }
}

bool Character::movechar(char direction, int boarder) //move character
{
    if(direction == 'w')
    {
        if(y > 0)
        {
            y -= 1;
            step++;
            return true;
        }
    }
    else if(direction == 'a')
    {
        if(x > 0)
        {
            x -= 1;
            step++;
            return true;
        }
    }
    else if(direction == 's')
    {
        if(y < boarder-1)
        {
            y += 1;
            step++;
            return true;
        }
    }
    else if(direction == 'd')
    {
        if(x < boarder-1)
        {
            x += 1;
            step++;
            return true;
        }
    }
    std::cout << std::endl;
    std::cout << "Invalid move! Try again: ";
    return false;
}

void Character::printStats() //prints current playerstats
{
    std::cout << "LEVEL " << level << std::endl;
    std::cout << std::endl;
    std::cout << std::setfill(' ') << std::setw(46) << "" << "Invisibility Potions: " << invisibilityPotion << std::endl;
    std::cout << std::setfill(' ') << std::setw(4) << "" << "Relics: " << relicPoints;
    std::cout << std::setfill(' ') << std::setw(39) << "" << "Flying Potions: " << flyingPotion << std::endl;
    std::cout << "Lifepoints: " << lifePoints;
    std::cout << std::setfill(' ') << std::setw(26) << "" << "Underwaterbreathing Potions: " << breathingPotion << std::endl;
    std::cout << std::setfill('_') << std::setw(70) << "" << std::endl;
    std::cout << std::endl;
}

int Character::actionDangerField(int danger) //lets the character react to the different kinds of dangerfields
{
    char choosepotion; //variable to choose a potion to flee the danger
    if(danger != 3 && danger != 2 && danger != 1) //empty dangerfield
    {
        return 0;
    }
    system("cls");
    printStats();
    std::cout << std::setfill('*') << std::setw(60) << "" << std::endl; //fills line with stars
    std::cout << std::setfill(' ') << std::setw(25) << "" << "!!DANGER!!" << std::endl; //prints text in the middle
    std::cout << std::setfill('*') << std::setw(60) << "" << std::endl;
    std::cout << std::endl;
    if(danger == 3) //different enemies for different kinds of danger
    {
        std::cout << "AN EAGLE IS CIRCLING YOU!" << std::endl;
    }
    else if(danger == 2)
    {
        std::cout << "YOU ENCOUNTERED AN AGGRESSIVE SWARM OF WASPS!" << std::endl;
    }
    else if(danger == 1)
    {
        std::cout << "WATCH OUT! A WILD BOAR IS ABOUT TO CHASE YOU!" << std::endl;
    }

    dangerMenu(); //prints infos on how to use the potions
    std::cin >> choosepotion;
    //depends on which potion was chosen
    if(choosepotion == 'i' && invisibilityPotion != 0)
    {
        invisibility(danger);
    }
    else if(choosepotion == 'u'&& breathingPotion != 0)
    {
        breathing(danger);
    }
    else if(choosepotion == 'f' && flyingPotion != 0)
    {
        fly(danger);
    }
    else if(choosepotion == 'i' || choosepotion == 'u' || choosepotion == 'f')
    {
        noPotion();
    }
    else
    {
        flee();
    }
    std::cout << "Continue by pressing any key." << std::endl;
    std::cin >> continueplaying;
    return 0;
}

void Character::invisibility(int danger) //an invisibility potion was chosen to flee a danger
{
    //change of character's attributes depends on the kind of danger the potion was used against
    if(danger == 3)
    {
        invisibilityPotion--;
        std::cout << "The eagle can't see you anymore. You fled successfully." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You fled an eagle successfully by using an invisibility potion.");
    }
    else if(danger == 2)
    {
        lifePoints--;
        invisibilityPotion--;
        std::cout << "The wasps sensed you anyways. You lost a life." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You used the wrong potion to flee a swarm of wasps. You lost a life.");
    }
    else if(danger == 1)
    {
        lifePoints--;
        invisibilityPotion--;
        std::cout << "The potion worked but you forgot to step out of the way. You lost a life." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You didn't manage to escape a boar. You lost a life.");
    }
}

void Character::breathing(int danger) //an underwaterbreathing potion was chosen
{
    //change of character's attributes depends on the kind of danger the potion was used against
    if(danger == 3)
    {
        lifePoints--;
        breathingPotion--;
        std::cout << "You tried to get into water but the eagle was faster than you. You lost a life. " << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You tried to flee an eagle by using the wrong potion. You lost a life.");
    }
    else if(danger == 2)
    {
        breathingPotion--;
        std::cout << "You fled into the water successfully." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You escaped a swarm of wasps by using an underwaterbreathing potion.");
    }
    else if(danger == 1)
    {
        lifePoints--;
        breathingPotion--;
        std::cout << "You tried to get to water but the boar was faster than you. You lost a life." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You didn't manage to escape a boar. You lost a life.");
    }
}

void Character::fly(int danger) //a flying potion was chosen
{
    //change of character's attributes depends on the kind of danger the potion was used against
    if(danger == 3)
    {
        lifePoints--;
        flyingPotion--;
        std::cout << "Flying was not the best idea. You lost a life." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You tried to flee an eagle by using the wrong potion. You lost a life.");
    }
    else if(danger == 2)
    {
        lifePoints--;
        flyingPotion--;
        std::cout << "Flying was not the best idea. You lost a life." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You used the wrong potion to flee a swarm of wasps. You lost a life.");
    }
    else if(danger == 1)
    {
        flyingPotion--;
        std::cout << "You escaped the boar successfully." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You successfully escaped a boar using a flying potion.");
    }
}

void Character::noPotion() //the character doesn't have the potion that was chosen
{
    std::cout << "You already used those potions up. You lost a life." << std::endl;
    addToHistory("\nStep " + std::to_string(step) + ": You tried to escape using a potion you ran out of. You lost a life.");
    lifePoints--;
}

void Character::flee() //no potion was chosen
{
    std::cout << "You tried to flee without a potion. It didn't work. You lost a life." << std::endl;
    addToHistory("\nStep " + std::to_string(step) + ": You tried to flee a danger without a potion. You lost a life.");
    lifePoints--;
}

void Character::dangerMenu() //prints instruction on how to use the potions
{
    std::cout << std::endl;
    std::cout << "Do you want to use a potion to flee? If so, which one?" << std::endl;
    std::cout << "(i: invisibility | f: fly | u: underwaterbreathing | any other key: no potion)" << std::endl;
}

void Character::actionFountainField() //character reacts to stepping on a fountain field
{
    system("cls");
    printStats();
    std::cout << std::setfill('*') << std::setw(60) << "" << std::endl; //fills line with stars
    std::cout << std::setfill(' ') << std::setw(25) << "" << "!!FOUNTAIN!!" << std::endl; //prints text in the middle
    std::cout << std::setfill('*') << std::setw(60) << "" << std::endl;
    std::cout << std::endl;
    int action = rand()%4; //4 options when stepping on a fountain field
    if(action == 3) //character heals
    {
        lifePoints++;
        std::cout << "The water of the fountain healed you. You gained one life." << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": The water of the fountain healed you. You gained one life.");
    }
    else if(action == 2) //invisibility potion found
    {
        invisibilityPotion++;
        std::cout << "You found an invisibility potion!" << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You found an invisibility potion!");
    }
    else if(action == 1) //underwaterbreathing potion found
    {
        breathingPotion++;
        std::cout << "You found an underwaterbreathing potion!" << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You found an underwaterbreathing potion!");
    }
    else //flying potion found
    {
        flyingPotion++;
        std::cout << "You found a flying potion!" << std::endl;
        addToHistory("\nStep " + std::to_string(step) + ": You found a flying potion!");
    }
    std::cout << "Press any key to continue playing." << std::endl;
    std::cin >> continueplaying;
}

void Character::increaseRelicPoints() //relic was found
{
    relicPoints++;
    addToHistory("\nStep " + std::to_string(step) + ": You found a relic!");
}

void Character::increaseLevel() //level up
{
    relicPoints = 0;
    x = 0;
    y = 0;
    step = 0;
    std::cout << std::setfill('*') << std::setw(100) << "" << std::endl; //fills line with stars
    std::cout << std::setfill(' ') << std::setw(25) << "" << "YOU COMPLETED LEVEL " << level << std::endl; //prints text in the middle
    std::cout << std::setfill('*') << std::setw(100) << "" << std::endl;
    level++;
    std::cout << "\nAre you ready for LEVEL " << level << "?" << std::endl;
    std::cout << "\nPress any key to start." << std::endl;
    addToHistory("\n\nLEVEL " + std::to_string(level) + ":");
}

void Character::die() //when the monster catches the player and they die
{
    lifePoints = 0;
    addToHistory("\nStep " + std::to_string(step) + ": The monster caught you. You died.");
}

void Character::addToHistory(std::string event) //adds new strings to the history
{
    history = history + event;
}

void Character::printHistory() //prints the history
{
    std::cout << history << std::endl;
}
