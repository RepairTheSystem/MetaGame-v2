#include <vector>
#include <windows.h>
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
    if (next_y >= height || next_y < 0 || next_x >= width || next_x < 0)
        next_cell_access = false;
    
    // Проверка на попытку пройти через препятствие 
    if (map[next_y][next_x] == '#')
        next_cell_access = false;

    if (next_cell_access)
        (player.*moveFunction)();
}

void PlayerInput(Player& player, Room* room) {
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        moveCheck(player, 0, -1, &Player::moveUp, room);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        moveCheck(player, 0, 1, &Player::moveDown, room);
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        moveCheck(player, -1, 0, &Player::moveLeft, room);
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        moveCheck(player, 1, 0, &Player::moveRight, room);
    }
    if (GetAsyncKeyState('B') & 0x8000) {
        room->addBullet(player.getX(), player.getY()-1);
    }
    if (GetAsyncKeyState('R') & 0x8000) {
        room->addRocket(player.getX(), player.getY()-1);
    }
}

#endif