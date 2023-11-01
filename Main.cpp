#include <iostream>
#include <vector>

#include "Cell.h"
#include "Room.h"
#include "GameFild.h"


using namespace std;

int main(){
    // Creating a game room
    Room room1(20, 10);

    // Adding objects to it
    room1.addBarrier(5, 5);
    room1.addBarrier(6, 5);

    room1.addMonster(1, 5);
    room1.addMonster(3, 5);
    room1.addTower(6, 2);
    
    room1.addChest(6, 0, 10);
    room1.addChest(10, 0, 30);
    
    // Creating a playing field based on the created room
    Game game(room1.getWidth(), room1.getHeight());
    game.setCurrentRoom(room1);

    // Start of the game
    game.start();
    return 0;
}