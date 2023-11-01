#ifndef Cell
#define Cell

#include <vector>
using namespace std;


// Этот класс будет представлять базовый объект в игре
// В нем можно хранить информацию о позиции, символе отображения и др.
class GameObject {
private:
    int x;
    int y;
    char symbol;
public:
    GameObject(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}

    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    
};

// Класс Препятствий
class Barrier : public GameObject {
public:
    Barrier(int x, int y) : GameObject(x, y, '#') {};
};

// Класс Сундуков
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