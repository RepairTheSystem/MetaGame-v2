#include "Cell.h"

using namespace std;

#ifndef Enemy
#define Enemy

// "Абстрактный" класс врагов
class Enemy : public GameObject {
public:
    Enemy(int x, int y, char symbol) : GameObject(x, y, symbol) {};

    // Проверяем, не подошел ли игрок слишком близко к врагу
    bool isEnemyClose(Player &player){
        if ((abs(getX() - player.getX()) + abs(getY() - player.getY())) <= 1)
            return true;
        return false;
    }
};

// Класс Башен - одного из возмжоных врагов
class Tower : public Enemy {
public: 
    Tower(int x, int y): Enemy(x, y, 'T') {};
};

// Класс монстров - одного из возможных врагов
class Monster : public Enemy {
public:
    Monster(int x, int y) : Enemy(x, y, 'M') {}

    // Метод для случайного движения монстра
    void moveRandom() {
        // Будем генерировать случайное число от 1 до 3-х, и в зависимости от числа
        // Будем моделировать шаги монстра
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