#include <vector>
#include <iostream>
#include <windows.h> // Это необходимо для корректного управления, без использования сторонних библиотек
#include "Cell.h"

#ifndef Control
#define Control

void moveCheck(Player& player, int xOffset, int yOffset, void (Player::*moveFunction)(), Room* room) {
    int height = room->getHeight();
    int width = room->getWidth();
    int next_y = player.getY() + yOffset;
    int next_x = player.getX() + xOffset;
    bool next_cell_access = true;
    vector<vector<char>> map = room->render();

    // Проверка на выпадение за карту
    if ((next_y <= height && next_y >= 0 && next_x <= width && next_x >= 0) == false)
        next_cell_access = false;
    
    // Проверка на попытку пройти через препятствие 
    if (map[next_y][next_x] == '#')
        next_cell_access = false;

    // Двигаем игрока, если все условия выполнены
    if (next_cell_access)
        (player.*moveFunction)();
}

void PlayerInput(Player& player, Room* room) {
    // Считываем передвижение игрока на стрелки
    if (GetAsyncKeyState(VK_UP)) {
        moveCheck(player, 0, -1, &Player::moveUp, room);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        moveCheck(player, 0, 1, &Player::moveDown, room);
    }
    if (GetAsyncKeyState(VK_LEFT)) {
        moveCheck(player, -1, 0, &Player::moveLeft, room);
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        moveCheck(player, 1, 0, &Player::moveRight, room);
    }
    // При нажатии на 'B' или 'R' создаем выстрел
    if (GetAsyncKeyState('B')) {
        room->addBullet(player.getX(), player.getY()-1);
    }
    if (GetAsyncKeyState('R')) {
        room->addRocket(player.getX(), player.getY()-1);
    }
}

#endif