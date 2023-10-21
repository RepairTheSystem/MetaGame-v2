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

class Bullet : public Projectile {
public:
    Bullet(int x, int y) : Projectile(x, y, 'B') {};
    
    bool isHitMonster(Monster& monster) {
        int bulletX = getX();
        int bulletY = getY();
        int monsterX = monster.getX();
        int monsterY = monster.getY();

        // Проверьте, если координаты пули и монстра совпадают
        if (bulletX == monsterX && bulletY == monsterY) {
            return true;
        }

        return false;
    }

};

class Rocket : public Projectile {
public:
    Rocket(int x, int y) : Projectile(x, y, 'R') {};
    
    bool isHitTower(Tower& tower) {
        int rocketX = getX();
        int rocketY = getY();
        int monsterX = tower.getX();
        int monsterY = tower.getY();

        // Проверьте, если координаты пули и монстра совпадают
        if (rocketX == monsterX && rocketY == monsterY) {
            return true;
        }

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
    vector<Projectile> projectiles;
    vector<Enemy> enemies;
    vector<Monster> monsters;
    vector<Tower> towers;
    vector<Bullet> bullets;
    vector<Rocket> rockets;
public:
    Room(int width, int height) : width(width), height(height), barriers(), enemies(),
    towers(), monsters(), bullets(), rockets() {
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
        for (const auto& shot : bullets) {
            roomMap[shot.getY()][shot.getX()] = shot.getSymbol();
        }

        // Отрисовать объекты Rocket в комнате
        for (const auto& shot : rockets) {
            roomMap[shot.getY()][shot.getX()] = shot.getSymbol();
        }

        /* if (true){
            // Отрисовать объекты Rocket в комнате
            auto it = rockets.begin(); // Это объявление оставьте как есть

            // Создадим итератор, который будет проверять нужно ли отрисовывать ракету
            // или удалить ее
            while (it != rockets.end()) {
                if (!it->isAlive()) {
                    it = rockets.erase(it); // Удаляем неактивные ракеты и получаем итератор на следующий элемент
                } 
                else {
                    roomMap[it->getY()][it->getX()] = it->getSymbol();
                    ++it; // Переходим к следующему элементу
                }
            } 
        }
        
        auto bulletIt = bullets.begin();
        while (bulletIt != bullets.end()) {
        
        auto monsterIt = monsters.begin();
        while (monsterIt != monsters.end()) {
            if (bulletIt->isHitMonster(*monsterIt)) {
                // Уничтожьте монстра
                monsterIt = monsters.erase(monsterIt);
                // Уничтожьте пулю
                bulletIt = bullets.erase(bulletIt);
            } 
            else {
                ++monsterIt;
            }
        }

        if (!bulletIt->isAlive()) {
            bulletIt = bullets.erase(bulletIt); // Удаляем неактивные пули
        } else {
            roomMap[bulletIt->getY()][bulletIt->getX()] = bulletIt->getSymbol();
            ++bulletIt;
        }
    } */
        

        return roomMap;
    }

    // Метод для проверки состояния пули - не попала ли она в монстра, или не вышла ли за карту
    void updateBullet() {
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            bulletIt->moveUp();

            for (auto monsterIt = monsters.begin(); monsterIt != monsters.end();) {
                if (bulletIt->isHitMonster(*monsterIt)) {
                    // Уничтожаем монстра
                    monsterIt = monsters.erase(monsterIt);

                    // Уничтожаем пулю
                    bulletIt = bullets.erase(bulletIt);

                    // Если оба итератора достигли конца, выходим из обоих циклов
                    if (monsterIt == monsters.end() && bulletIt == bullets.end())
                        return;
                } 
                else {
                    // Двигаем итератор монстра
                    ++monsterIt;
                }
            }
            // Если закончились пули - заканчиваем цикл
            if (bulletIt == bullets.end()) {
                return;
            }
            // Удаляем пулю из массива, если она мертва
            else if (!bulletIt->isAlive()) {
                bulletIt = bullets.erase(bulletIt);
            } 
            else {
                // Двигаем итератор пули
                ++bulletIt;
            }
        }
    }   

    // Метод для проверки состояния ракеты - не попала она в башню, или не вышла ли за карту
    void updateRocket() {
        for (auto rocketIt = rockets.begin(); rocketIt != rockets.end();) {
            rocketIt->moveUp();

            for (auto towerIt = towers.begin(); towerIt != towers.end();) {
                if (rocketIt->isHitTower(*towerIt)) {
                    // Уничтожаем башню
                    towerIt = towers.erase(towerIt);

                    // Уничтожаем ракету
                    rocketIt = rockets.erase(rocketIt);

                    // Если оба итератора достигли конца, выходим из обоих циклов
                    if (towerIt == towers.end() && rocketIt == rockets.end())
                        return;
                }
                else {
                    // Двигаем итератор башни
                    ++towerIt;
                }
            }
            // Если закончились ракеты - заканчиваем цикл
            if (rocketIt == rockets.end()) {
                return;
            }
            // Удаляем ракету из массива, если она мертва
            else if (!rocketIt->isAlive()) {
                rocketIt = rockets.erase(rocketIt);
            } 
            else {
                // Двигаем итератор ракеты
                ++rocketIt;
            }
        }
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