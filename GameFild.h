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
public:
    Game(int width, int height) : width(width), height(height), player(0, 0) {
        // Создаем карту игры
        map = vector<vector<char>>(height, vector<char>(width, '.'));
    }

    void render() {
        system("cls");
        // Отрисовываем карту игры и игрока
        // Здесь вы можете добавить отрисовку других объектов и комнат
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (x == player.getX() && y == player.getY()) {
                    cout << player.getSymbol();
                } else {
                    cout << map[y][x];
                }
            }
            cout << endl;
        }
        PlayerInput(player, width, height);
        Sleep(300);
    }
};



#endif