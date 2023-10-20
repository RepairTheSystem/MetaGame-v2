#include <vector>
#include <windows.h>
#include "Cell.h"

#ifndef Control
#define Control

void moveCheck(Player& player, int xOffset, int yOffset, void (Player::*moveFunction)(), int width, int height, vector<vector<char>> map) {
    int next_y = player.getY() + yOffset;
    int next_x = player.getX() + xOffset;
    bool next_cell_access = true;

    // Проверка на выпадение за карту
    if (next_y >= height || next_y < 0 || next_x >= width || next_x < 0)
        next_cell_access = false;
    
    // Проверка на попытку пройти в препятствие 
    if (map[next_y][next_x] == '#')
        next_cell_access = false;

    if (next_cell_access)
        (player.*moveFunction)();
}

void PlayerInput(Player& player, int width, int height, vector<vector<char>> map) {
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        moveCheck(player, 0, -1, &Player::moveUp, width, height, map);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        moveCheck(player, 0, 1, &Player::moveDown, width, height, map);
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        moveCheck(player, -1, 0, &Player::moveLeft, width, height, map);
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        moveCheck(player, 1, 0, &Player::moveRight, width, height, map);
    }
    /* 
    if (GetAsyncKeyState('R') & 0x8000) {
        Shot* projectile = player.create_shot();
        if (projectile != nullptr)
            bullets.push_back(*projectile);
    } */
}

#endif