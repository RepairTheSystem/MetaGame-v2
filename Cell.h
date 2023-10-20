#
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
    Enemy(int x, int y, char symbol) : GameObject(x, y, symbol) {};

    // Проверяем, не подошел ли игрок слишком близко к врагу
    bool isEnemyClose(Player &player){
        if ((abs(getX() - player.getX()) + abs(getY() - player.getY())) <= 1)
            return true;
        return false;
    }
};

class Tower : public Enemy {
public: 
    Tower(int x, int y): Enemy(x, y, 'T') {};
};

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

class Room {
private:
    // Класс, представляющий комнату в игре
    // Здесь будем хранить информацию о комнате, ее размере, объектах и т. д.
    int width;
    int height;
    vector<vector<char>> roomMap;
    vector<Barrier> barriers;
    vector<Monster> monsters;
    vector<Tower> towers;
    vector<Enemy> enemies;
public:
    Room(int width, int height) : width(width), height(height), barriers(), enemies(), towers(), monsters(){
        // Создадим комнату заданного размера   
        roomMap = vector<vector<char>>(height, vector<char>(width, '.'));
    }

    // Методы для добавления объектов Barrier и Enemy в комнату
    void addBarrier(int x, int y) {
        barriers.push_back(Barrier(x, y));
    }

    void addTower(int x, int y) {
        Tower tower(x, y);
        towers.push_back(tower);
    }

    void addMonster(int x, int y) {
        Monster monster(x, y);
        monsters.push_back(monster);
    }


    // Передаем всех злых существ
    vector<Enemy> getEnemies(){
        // Объединяем врагов из разных векторов
        enemies.clear(); // Очищаем текущий вектор
        enemies.insert(enemies.end(), towers.begin(), towers.end());
        enemies.insert(enemies.end(), monsters.begin(), monsters.end());
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

    // Метод передачи указателей на всех монстров в комнате 
    vector<Monster*> getMonsters() {
        vector<Monster*> monsterPointers;
        for (Monster& monster : monsters) {
            monsterPointers.push_back(&monster);
        }
    return monsterPointers;
}
};

#endif