#include "Cell.h"

#ifndef Character
#define Character

// Player Class
class Player : public GameObject {
private: int score;
public:
    Player(int x, int y) : GameObject(x, y, 'P'), score(0) {};
    // Methods for updating a player's position
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
    // Methods for working with a player's score
    int getScore() const {
        return score;
    }
    void addScore(int givenScore){
        int newScore = givenScore + getScore();
        score = newScore;
    }
    // a method for checking a chest in a cage with a player
    bool isChestInCell (Chest& chest) {
        int chestX = chest.getX();
        int chestY = chest.getY();

        if (getX() == chestX && getY() == chestY)
            return true;
        return false;
    }
};

#endif