#ifndef Fild123
#define Fild123

#include <vector>
#include <iostream>
#include <thread>


#include "Contol.h"
#include "Room.h"
#include "Player.h"

using namespace std;

class Game {
    // Основной класс игры
private:
    int width;
    int height;
    vector<vector<char>> map;
    Player player;
    Room* currentRoom;
public:
    Game(int width, int height) : width(width), height(height), player(1, 1) {
        // Создаем карту игры
        map = vector<vector<char>>(height, vector<char>(width, '.'));
        currentRoom = nullptr;
    }
    
    // Метод задающий текущую комнату
    void setCurrentRoom(Room& room) {
        currentRoom = &room;
    }

    void render() {
        system("cls");
        // Отрисовываем карту игры и игрока
        // Отображаем текущую комнату и ее наполнение 
        if (currentRoom != nullptr) {
            map = currentRoom->render();
        }

        map[player.getY()][player.getX()] = player.getSymbol();
        
        // Перебираем врагов и проверяем, не слишком ли они близко к игроку
        for (Enemy enemy : currentRoom->getEnemies()) {
            if (enemy.isEnemyClose(player)) {
                // Враг слишком близко к игроку, меняем символ и останавливаем игру
                map[player.getY()][player.getX()] = 'D';
                cout << "Game Over!" << endl;
                
                cin.get();
                exit(0); // Останавливаем игру
            }
        }
        
        // Передвигаем выстрелы вверх
        currentRoom->updateBullet();
        currentRoom->updateRocket();

        // Обновляем сундуки 
        currentRoom->updateChest(player);

        // Применяем рандомное передвижение монстров
        for (Monster* monster : currentRoom->getMonsters()) {
            monster->moveRandom();
        }

        // Отобразим карту игры
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cout << map[y][x];
            }
            cout << endl;
        }
        // Выводим счет игрока
        cout << "Score: " << player.getScore();
        PlayerInput(player, currentRoom);
        this_thread::sleep_for(chrono::milliseconds(300));
    }
};

#endif