#include <iostream>
#include <vector>

#include "Cell.h"
#include "GameFild.h"

using namespace std;

int main(){
    // Создаем объект игры
    Room room1(20, 10);
    room1.addBarrier(5, 5);
    room1.addBarrier(6, 5);

    room1.addEnemy(1, 5);

    Game game(room1.getWidth(), room1.getHeight());
    game.setCurrentRoom(room1);
    // Основной цикл игры
    while (true) {
        game.render();
    }
    return 0;
}