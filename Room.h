#ifndef GameRoom
#define GameRoom

#include "Enemy.h"
#include "Bullet.h"
#include "Cell.h"
#include "Player.h"
// A class representing a room in the game
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
        // Create a room of a given size
        roomMap = vector<vector<char>>(height, vector<char>(width, '.'));
    }

    // Methods for adding Barrier objects to a room
    void addBarrier(int x, int y) {
        barriers.push_back(Barrier(x, y));
    }

    // Methods for adding Tower objects to a room
    void addTower(int x, int y) {
        Tower tower(x, y);
        towers.push_back(tower);
    }

    // Methods for adding Monster objects to a room
    void addMonster(int x, int y) {
        Monster monster(x, y);
        monsters.push_back(monster);
    }

    // Methods for adding Bullet objects to a room
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

    // We pass all evil creatures
    vector<Enemy> getEnemies(){
        // Объединяем врагов из разных векторов
        enemies.clear(); // Очищаем текущий вектор
        enemies.insert(enemies.end(), towers.begin(), towers.end());
        enemies.insert(enemies.end(), monsters.begin(), monsters.end());
        return enemies;
    }

    // Methods for displaying objects in a room
    vector<vector<char>> render() {
        // Clearing the room map
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                roomMap[y][x] = '.';
            }
        }

        // Drawing Barrier objects in the room
        for (const auto& barrier : barriers) {
            roomMap[barrier.getY()][barrier.getX()] = barrier.gettexture();
        }

        // Drawing the Enemy objects in the room
        for (const auto& enemy : enemies) {
            roomMap[enemy.getY()][enemy.getX()] = enemy.gettexture();
        }

        // Drawing Bullet objects in the room
        for (const auto& shot : bullets) {
            roomMap[shot.getY()][shot.getX()] = shot.gettexture();
        }

        // Drawing Rocket objects in the room
        for (const auto& shot : rockets) {
            roomMap[shot.getY()][shot.getX()] = shot.gettexture();
        }
        
        // Drawing Chest objects in the room
        for (const auto& chest : chests) {
            roomMap[chest.getY()][chest.getX()] = chest.gettexture();
        }

        return roomMap;
    }

    // The method for checking the condition of the bullet is whether it hit the monster, or whether it went beyond the map
    void updateBullet() {
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
            bulletIt->moveUp();

            for (auto monsterIt = monsters.begin(); monsterIt != monsters.end();) {
                if (bulletIt->isHitMonster(*monsterIt)) {
                    // Destroying the monster
                    monsterIt = monsters.erase(monsterIt);

                    // Destroying the bullet
                    bulletIt = bullets.erase(bulletIt);

                    // If both iterators have reached the end, exit both loops
                    if (monsterIt == monsters.end() && bulletIt == bullets.end())
                        return;
                } 
                else {
                    // Moving the monster iterator
                    ++monsterIt;
                }
            }
            // If the bullets have run out, we end the cycle
            if (bulletIt == bullets.end()) {
                return;
            }
            // Removing the bullet from the array if it is dead
            else if (!bulletIt->isAlive()) {
                bulletIt = bullets.erase(bulletIt);
            } 
            else {
                // Moving the bullet iterator
                ++bulletIt;
            }
        }
    }   

    // Method for checking the state of the rocket - did it hit the tower, or did it go beyond the map
    void updateRocket() {
        for (auto rocketIt = rockets.begin(); rocketIt != rockets.end();) {
            rocketIt->moveUp();

            for (auto towerIt = towers.begin(); towerIt != towers.end();) {
                if (rocketIt->isHitTower(*towerIt)) {
                    // Destroying the tower
                    towerIt = towers.erase(towerIt);

                    // Destroying the rocket
                    rocketIt = rockets.erase(rocketIt);

                    // If both iterators have reached the end, exit both loops
                    if (towerIt == towers.end() && rocketIt == rockets.end())
                        return;
                }
                else {
                    // Moving the tower iterator
                    ++towerIt;
                }
            }
            // If the rockets have run out, we finish the cycle
            if (rocketIt == rockets.end()) {
                return;
            }
            // Removing the rocket from the array if it is dead
            else if (!rocketIt->isAlive()) {
                rocketIt = rockets.erase(rocketIt);
            } 
            else {
                // Moving the rocket iterator
                ++rocketIt;
            }
        }
    }

    
    // Check if the player has not got into the cell with the chest, and if necessary,
    // add points in the method of the Game class
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

    // The method of passing pointers to all the monsters in the room
    vector<Monster*> getMonsters() {
        vector<Monster*> monsterPointers;
        for (Monster& monster : monsters) {
            monsterPointers.push_back(&monster);
        }
        return monsterPointers;
    }

};

#endif