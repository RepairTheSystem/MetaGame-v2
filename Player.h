#include "Cell.h"

#ifndef Character
#define Character

// Класс игрока
class Player : public GameObject {
private: int score;
public:
    Player(int x, int y) : GameObject(x, y, 'P'), score(0) {};
    // Методы для обновления позиции игрока
    void moveUp() { 
        int currentY = getY();
        setY(currentY-1); 
    }
    void moveDown() { 
        int currentY = getY();
        setY(currentY+1); 
    }
    void moveRight() { 
        int currentX = getX();
        setX(currentX+1); 
    }
    void moveLeft() { 
        int currentX = getX();
        setX(currentX-1); 
    }
    // Методы для работы с счетом игрока
    int getScore() const {
        return score;
    }
    void addScore(int givenScore){
        int newScore = givenScore + getScore();
        score = newScore;
    }
    bool isChestInCell (Chest& chest) {
        int chestX = chest.getX();
        int chestY = chest.getY();

        if (getX() == chestX && getY() == chestY)
            return true;
        return false;
    }
};

#endif