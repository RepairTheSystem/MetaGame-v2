#ifndef Cell
#define Cell

#include <vector>
using namespace std;


// This class will represent the base object in the game
// It can store information about the position, display symbol, etc.
class GameObject {
private:
    int x;
    int y;
    char texture;
public:
    GameObject(int x, int y, char texture) : x(x), y(y), texture(texture) {}

    int getX() const { return x; }
    int getY() const { return y; }
    char gettexture() const { return texture; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    
};

// Obstacle Class
class Barrier : public GameObject {
public:
    Barrier(int x, int y) : GameObject(x, y, '#') {};
};

// Chest Class
class Chest : public GameObject {
private:
    int score;
public:
    Chest(int x, int y, int score) : GameObject(x, y, 'C'), score(score) {};

    int getScore() {
        return score;
    }
};

#endif