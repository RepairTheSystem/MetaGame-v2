#ifndef Bullet123
#define Bullet123

#include "Cell.h"
#include "Enemy.h"
#include <vector>
using namespace std;

// "Абстрактный" класс выстрелов 
class Projectile : public GameObject {
private:
    bool isAliveV;
public:
    Projectile (int x, int y, char symbol) : GameObject(x, y, symbol), isAliveV(true) {};
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

// Класс Пуль - одного из вида выстрелов
class Bullet : public Projectile {
public:
    Bullet (int x, int y) : Projectile(x, y, 'B') {};
    
    // Метод проверки на близость пули к монстру
    bool isHitMonster(Monster& monster) {
        int bulletX = getX();
        int bulletY = getY();
        int monsterX = monster.getX();
        int monsterY = monster.getY();

        // Если координаты пули и монстра совпадают
        if (bulletX == monsterX && bulletY == monsterY) {
            return true;
        }

        return false;
    }

};

// Класс Ракет - одного из видов выстрелов 
class Rocket : public Projectile {
public:
    Rocket(int x, int y) : Projectile(x, y, 'R') {};
    
    // Метод проверки на близость к башне
    bool isHitTower(Tower& tower) {
        int rocketX = getX();
        int rocketY = getY();
        int monsterX = tower.getX();
        int monsterY = tower.getY();

        // Если координаты пули и монстра совпадают
        if (rocketX == monsterX && rocketY == monsterY) {
            return true;
        }

        return false;
    }
};


#endif