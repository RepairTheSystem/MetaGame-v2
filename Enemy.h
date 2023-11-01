#ifndef EvilCreature
#define EvilCreature

#include "Cell.h"
#include "Player.h"
#include "cstdlib"
using namespace std;


// "Abstract" enemy class
class Enemy : public GameObject {
public:
    Enemy(int x, int y, char texture) : GameObject(x, y, texture) {};

    // Проверяем, не подошел ли игрок слишком близко к врагу
    bool isEnemyClose(Player &player){
        if ((abs(getX() - player.getX()) + abs(getY() - player.getY())) <= 1)
            return true;
        return false;
    }
};

// Tower Class - one of the possible enemies
class Tower : public Enemy {
public: 
    Tower(int x, int y): Enemy(x, y, 'T') {};
};

// Monster class - one of the possible enemies
class Monster : public Enemy {
public:
    Monster(int x, int y) : Enemy(x, y, 'M') {}

    // Method for random monster movement
    void moveRandom() {
        // We will generate a random number from 1 to 3, and depending on the number
        // We will simulate the steps of the monster
        int moveSeed = rand() % 3;
        if(moveSeed == 0)
            moveUp();
        if(moveSeed == 1)
            moveDown();
    }
    void moveUp() { 
        int currentY = getY();
        if (currentY >= 1)
            setY(currentY-1); 
    }
    void moveDown() { 
        int currentY = getY();
        setY(currentY+1); 
    }
};

#endif