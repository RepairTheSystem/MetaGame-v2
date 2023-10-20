using namespace std;

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
public:
    Barrier(int x, int y) : GameObject(x, y, '#') {};
};

class Enemy : public GameObject {
public:
    Enemy(int x, int y) : GameObject(x, y, 'E') {};

    // Проверяем, не подошел ли игрок слишком близко к врагу
    bool isEnemyClose(Player &player){
        if ((abs(getX() - player.getX()) + abs(getY() - player.getY())) <= 1)
            return true;
        return false;
    }
};

class Room {
private:
    // Класс, представляющий комнату в игре
    // Здесь будем хранить информацию о комнате, ее размере, объектах и т. д.
    int width;
    int height;
    vector<vector<char>> roomMap;
    vector<Barrier> barriers;
    vector<Enemy> enemies;
public:
    Room(int width, int height) : width(width), height(height), barriers(), enemies() {
        // Создадим комнату заданного размера   
        roomMap = vector<vector<char>>(height, vector<char>(width, '.'));
    }

    // Методы для добавления объектов Barrier и Enemy в комнату
    void addBarrier(int x, int y) {
        barriers.push_back(Barrier(x, y));
    }

    void addEnemy(int x, int y) {
        enemies.push_back(Enemy(x, y));
    }

    vector<Enemy> getEnemies(){
        return enemies;
    }

    // Методы для отображения объектов в комнате
    vector<vector<char>> render() {
        // Очистите карту комнаты
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                roomMap[y][x] = '.';
            }
        }

        for (const auto& barrier : barriers) {
            // Отрисовать объекты Barrier в комнате
            roomMap[barrier.getY()][barrier.getX()] = barrier.getSymbol();
        }

        for (const auto& enemy : enemies) {
            // Отрисовать объекты Enemy в комнате
            roomMap[enemy.getY()][enemy.getX()] = enemy.getSymbol();
        }
        return roomMap;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
};

#endif