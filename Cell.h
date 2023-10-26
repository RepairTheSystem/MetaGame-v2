#include <vector>
using namespace std;

#ifndef Cell
#define Cell

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

    // Проверка на наличие игрока в клетке
    bool isPlayerClose (Player& player) {
        int playerX = player.getX();
        int playerY = player.getY();

        if (getX() == playerX && getY() == playerY)
            return true;
        return false;
    }

    int getScore() {
        return score;
    }
};

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

// "Абстрактный" класс выстрелов 
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

// Класс Пуль - одного из вида выстрелов
class Bullet : public Projectile {
public:
    Bullet(int x, int y) : Projectile(x, y, 'B') {};
    
    // Метод проверки на близость пули к монстру
    bool isHitMonster(Monster& monster) {
        int bulletX = getX();
        int bulletY = getY();
        int monsterX = monster.getX();
        int monsterY = monster.getY();

        // Если координаты пули и монстра совпадают
        if (bulletX == monsterX && bulletY == monsterY) {
            return true;
        }

        return false;
    }

};

// Класс Ракет - одного из видов выстрелов 
class Rocket : public Projectile {
public:
    Rocket(int x, int y) : Projectile(x, y, 'R') {};
    
    // Метод проверки на близость к башне
    bool isHitTower(Tower& tower) {
        int rocketX = getX();
        int rocketY = getY();
        int monsterX = tower.getX();
        int monsterY = tower.getY();

        // Если координаты пули и монстра совпадают
        if (rocketX == monsterX && rocketY == monsterY) {
            return true;
        }

        return false;
    }
};

// Класс, представляющий комнату в игре
class Room {
private:
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
    vector<Chest> chests;
public:
    Room(int width, int height) : width(width), height(height), barriers(), enemies(),
    towers(), monsters(), bullets(), rockets(), chests() {
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

    void addChest (int x, int y, int cost){
        Chest chest(x, y, cost);
        chests.push_back(chest);
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
        // Очищаем карту комнаты
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                roomMap[y][x] = '.';
            }
        }

        // Отрисовываем объекты Barrier в комнате
        for (const auto& barrier : barriers) {
            roomMap[barrier.getY()][barrier.getX()] = barrier.getSymbol();
        }

        // Отрисовываем объекты Enemy в комнате
        for (const auto& enemy : enemies) {
            roomMap[enemy.getY()][enemy.getX()] = enemy.getSymbol();
        }

        // Отрисовываем объекты Bullet в комнате
        for (const auto& shot : bullets) {
            roomMap[shot.getY()][shot.getX()] = shot.getSymbol();
        }

        // Отрисовываем объекты Rocket в комнате
        for (const auto& shot : rockets) {
            roomMap[shot.getY()][shot.getX()] = shot.getSymbol();
        }
        
        // Отрисовываем объекты Chest в комнате
        for (const auto& chest : chests) {
            roomMap[chest.getY()][chest.getX()] = chest.getSymbol();
        }

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

    // Проверяем, не попал ли игрок в клетку с сундуком, и при необходимости прибавляем очки
    void updateChest(Player& player) {
        for (auto chestIt = chests.begin(); chestIt != chests.end();){
            if (chestIt->isPlayerClose(player)){
                player.addScore(chestIt->getScore());
                chestIt = chests.erase(chestIt);
            }
            else{
                ++chestIt;
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

};

#endif