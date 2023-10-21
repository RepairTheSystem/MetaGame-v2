#include <vector>
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

class Projectile : public GameObject {
public:
    Projectile (int x, int y, char symbol) : GameObject(x, y, symbol) {};
    void moveUp() { 
        int currentY = getY();
        if (currentY >= 1)
            setY(currentY-1); 
    }
};

class Bullet : public Projectile {
public:
    Bullet(int x, int y) : Projectile(x, y, 'B') {};
    
};

class Rocket : public Projectile {
public:
    Rocket(int x, int y) : Projectile(x, y, 'R') {};
    
};
class Room {
private:
    // Класс, представляющий комнату в игре
    // Здесь будем хранить информацию о комнате, ее размере, объектах и т. д.
    int width;
    int height;
    vector<vector<char>> roomMap;
    vector<Barrier> barriers;
    vector<Projectile> projectiles;
    vector<Enemy> enemies;
    vector<Monster> monsters;
    vector<Tower> towers;
    vector<Bullet> bullets;
    vector<Rocket> rockets;
public:
    Room(int width, int height) : width(width), height(height), barriers(), enemies(), towers(), monsters(){
        // Создадим комнату заданного размера   
        roomMap = vector<vector<char>>(height, vector<char>(width, '.'));
    }

    // Методы для добавления объектов Barrier в комнату
    void addBarrier(int x, int y) {
        barriers.push_back(Barrier(x, y));
    }

    // Методы для добавления объектов Tower в комнату
    void addTower(int x, int y) {
        Tower tower(x, y);
        towers.push_back(tower);
    }

    // Методы для добавления объектов Monster в комнату
    void addMonster(int x, int y) {
        Monster monster(x, y);
        monsters.push_back(monster);
    }

    // Методы для добавления объектов Bullet в комнату
    void addBullet (int x, int y) {
        Bullet bullet(x, y);
        bullets.push_back(bullet);
        projectiles.push_back(bullet);
    }
    
    void addRocket (int x, int y) {
        Rocket rocket(x, y);
        rockets.push_back(rocket);
        projectiles.push_back(rocket);
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

        // Отрисовать объекты Barrier в комнате
        for (const auto& barrier : barriers) {
            roomMap[barrier.getY()][barrier.getX()] = barrier.getSymbol();
        }

        // Отрисовать объекты Enemy в комнате
        for (const auto& enemy : enemies) {
            roomMap[enemy.getY()][enemy.getX()] = enemy.getSymbol();
        }
        
        // Отрисовать объекты Bullet в комнате
        for (const auto& projectile : bullets) {
            roomMap[projectile.getY()][projectile.getX()] = projectile.getSymbol();
        }
        
        // Отрисовать объекты Rocket в комнате
        for (const auto& projectile : rockets) {
            roomMap[projectile.getY()][projectile.getX()] = projectile.getSymbol();
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

    // Передаем все указатели на снаряды на карте 
    vector<Projectile*> getProjectiles() {
        vector<Projectile*> shotPointers;
        for (Projectile& shot : bullets) {
            shotPointers.push_back(&shot);
        }
        for (Projectile& shot : rockets) {
            shotPointers.push_back(&shot);
        }

        return shotPointers;
    }

};

#endif