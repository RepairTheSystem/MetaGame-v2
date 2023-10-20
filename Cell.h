#ifndef Cell
#define Cell
class GameObject {
    // Этот класс будет представлять базовый объект в игре
    // В нем можно хранить информацию о позиции, символе отображения и др.
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
class Player : public GameObject {
    // Класс игрока - наследник базового класса GameObject
public:
    Player(int x, int y) : GameObject(x, y, 'P') {}
    // Добавьте здесь методы для управления игроком, такие как move, attack, и т. д.
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
};

class Barrier : public GameObject {
    Barrier(int x, int y) : GameObject(x, y, '#') {};
};

class Enemy : public GameObject {
    Enemy(int x, int y) : GameObject(x, y, 'E') {};
};

class Room {
    // Класс, представляющий комнату в игре
    // Здесь вы можете хранить информацию о комнате, ее размере, объектах и т. д.
};

#endif