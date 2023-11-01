#ifndef Room123
#define Room123

#include "Enemy.h"
#include "Bullet.h"
#include "Cell.h"
#include "Player.h"

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

    
    // Проверяем, не попал ли игрок в клетку с сундуком, и при необходимости прибавляем очки в методе класса Game
    void updateChest(Player& player) {
        for (auto chestIt = chests.begin(); chestIt != chests.end();) {
            if (player.isChestInCell(*chestIt)) {
                player.addScore(chestIt->getScore());
                chestIt = chests.erase(chestIt);
            } 
            else {
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