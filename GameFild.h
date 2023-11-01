#ifndef GameFild
#define GameFild

#include <vector>
#include <iostream>
#include <thread>

#include "Contol.h"
#include "Room.h"
#include "Player.h"

using namespace std;

// Main class of the game
class Game {
private:
    int width;
    int height;
    vector<vector<char>> map;
    Player player;
    Room* currentRoom;
public:
    // Creating a game map
    Game(int width, int height) : width(width), height(height), player(1, 1) {
        map = vector<vector<char>>(height, vector<char>(width, '.'));
        currentRoom = nullptr;
    }
    
    // The method that sets the current room
    void setCurrentRoom(Room& room) {
        currentRoom = &room;
    }

    // The method that calculates the map update 
    void render() {
        system("cls");
        //Drawing the map of the game and the player
        // Displays the current room and its contents
        if (currentRoom != nullptr) {
            map = currentRoom->render();
        }

        map[player.getY()][player.getX()] = player.gettexture();
        
        // We sort through the enemies and check if they are too close to the player
        for (Enemy enemy : currentRoom->getEnemies()) {
            if (enemy.isEnemyClose(player)) {
                // The enemy is too close to the player, change the symbol and stop the game
                map[player.getY()][player.getX()] = 'D';
                cout << "Game Over!" << endl;
                
                cin.get();
                exit(0); // Stopping the game
            }
        }
        
        // Moving the shots up
        currentRoom->updateBullet();
        currentRoom->updateRocket();

        // Updating chests
        currentRoom->updateChest(player);

        // Randomly move monsters
        for (Monster* monster : currentRoom->getMonsters()) {
            monster->moveRandom();
        }

        // Display the game map
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cout << map[y][x];
            }
            cout << endl;
        }
        // We output the player's account
        cout << "Score: " << player.getScore();
        PlayerInput(player, currentRoom);
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    // The method that starts the game cycle
    void start(){
        while (true){
            render();
        }
    }

};

#endif