#ifndef PlayerControl
#define PlayerControl

#include <vector>
#include <iostream>
#include <windows.h> // This is necessary for correct control, without using third-party libraries
#include "Room.h"


void moveCheck(Player& player, int xOffset, int yOffset, void (Player::*moveFunction)(), Room* room) {
    int height = room->getHeight();
    int width = room->getWidth();
    int next_y = player.getY() + yOffset;
    int next_x = player.getX() + xOffset;
    bool next_cell_access = true;
    vector<vector<char>> map = room->render();

    // Check for emptiness to move 
    // Check for card loss
    if ((next_y <= height && next_y >= 0 && next_x <= width && next_x >= 0) == false)
        next_cell_access = false;
    
    // Check for an attempt to pass through an obstacle
    if (map[next_y][next_x] == '#')
        next_cell_access = false;

    // Move the player if all conditions are met
    if (next_cell_access)
        (player.*moveFunction)();
}

void PlayerInput(Player& player, Room* room) {
    // Reading the player's movement on the arrows
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
    // When you click on 'B' or 'R', we create a shot
    if (GetAsyncKeyState('B')) {
        room->addBullet(player.getX(), player.getY()-1);
    }
    if (GetAsyncKeyState('R')) {
        room->addRocket(player.getX(), player.getY()-1);
    }
}

#endif