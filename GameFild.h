#include <vector>
#include <iostream>
#include <windows.h>

#include "Cell.h"
#include "Contol.h"

using namespace std;

#ifndef Fild
#define Fild

class Game {
    // Основной класс игры
private:
    int width;
    int height;
    vector<vector<char>> map;
    Player player;
    Room* currentRoom;
public:
    Game(int width, int height) : width(width), height(height), player(0, 0) {
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
        // Отобразите текущую комнату и её содержимое
        if (currentRoom != nullptr) {
            map = currentRoom->render();
        }

        map[player.getY()][player.getX()] = player.getSymbol();

        // Отобразите карту игры
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cout << map[y][x];
            }
            cout << endl;
        }
        
        PlayerInput(player, width, height);
        Sleep(300);
    }
};



#endif