#include <vector>
#include <windows.h>
#include "Cell.h"

#ifndef Control
#define Control

void moveCheck(Player& player, int x_offset, int y_offset, void (Player::*moveFunction)(), int width, int height) {
    int next_y = player.getY() + y_offset;
    int next_x = player.getX() + x_offset;
    bool next_cell_access = true;
    /* 
    for (const Block& block : blocks) {
        if (next_x == block.get_x() && next_y == block.get_y()) {
            next_cell_access = false;
            break;
        }
    }
     */
    if(next_y >= height || next_y < 0 || next_x >= width || next_x < 0)
        next_cell_access = false;

    if (next_cell_access)
        (player.*moveFunction)();
}

void PlayerInput(Player& player, int width, int height) {
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        moveCheck(player, 0, -1, &Player::moveUp, width, height);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        moveCheck(player, 0, 1, &Player::moveDown, width, height);
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        moveCheck(player, -1, 0, &Player::moveLeft, width, height);
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        moveCheck(player, 1, 0, &Player::moveRight, width, height);
    }
    /* 
    if (GetAsyncKeyState('R') & 0x8000) {
        Shot* projectile = player.create_shot();
        if (projectile != nullptr)
            bullets.push_back(*projectile);
    } */
}

#endif