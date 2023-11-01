#ifndef Shot
#define Shot

#include "Cell.h"
#include "Enemy.h"
#include <vector>
using namespace std;

// "Abstract" class of shots
class Projectile : public GameObject {
private:
    bool isAliveV;
public:
    Projectile (int x, int y, char texture) : GameObject(x, y, texture), isAliveV(true) {};
    void moveUp() { 
        int currentY = getY();
        if (currentY >= 1 and isAlive())
            setY(currentY-1); 
        else
            isAliveV = false;
    }
    bool isAlive() const {
        return isAliveV;
    }
};

// The class of bullets is one of the types of shots
class Bullet : public Projectile {
public:
    Bullet (int x, int y) : Projectile(x, y, 'B') {};
    
    // The method of checking for the proximity of the bullet to the monster
    bool isHitMonster(Monster& monster) {
        int bulletX = getX();
        int bulletY = getY();
        int monsterX = monster.getX();
        int monsterY = monster.getY();

        // If the coordinates of the bullet and the monster match
        if (bulletX == monsterX && bulletY == monsterY) {
            return true;
        }

        return false;
    }

};

// Rockets class - one of the types of shots
class Rocket : public Projectile {
public:
    Rocket(int x, int y) : Projectile(x, y, 'R') {};
    
    // The method of checking for proximity to the tower
    bool isHitTower(Tower& tower) {
        int rocketX = getX();
        int rocketY = getY();
        int towerX = tower.getX();
        int towerY = tower.getY();

        // If the coordinates of the bullet and the tower match
        if (rocketX == towerX && rocketY == towerY) {
            return true;
        }

        return false;
    }
};


#endif