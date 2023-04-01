#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
private:
    int level;
    int lifePoints;
    int relicPoints;
    int x;
    int y;
    int step;
    int invisibilityPotion;
    int flyingPotion;
    int breathingPotion;
    char continueplaying;
    std::string history;

public:
    Character();
    int getLifePoints();
    int getLevel();
    int getX();
    int getY();
    void setLifePoints();
    void increaseRelicPoints();
    void increaseLevel();
    bool movechar(char direction, int boarder);
    void dangerMenu();
    int actionDangerField(int danger);
    void actionFountainField();
    void invisibility(int danger);
    void breathing(int danger);
    void fly(int danger);
    void noPotion();
    void flee();
    void die();
    void printStats();
    void addToHistory(std::string event);
    void printHistory();
};

#endif
