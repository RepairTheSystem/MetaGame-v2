#include <iostream>
#include <vector>

#include "Cell.h"
#include "Room.h"
#include "GameFild.h"


using namespace std;

int main(){
    // Создаем комнату игры
    Room room1(20, 10);

    // Добавляем в нее объекты
    room1.addBarrier(5, 5);
    room1.addBarrier(6, 5);

    room1.addMonster(1, 5);
    room1.addMonster(3, 5);
    room1.addTower(6, 2);
    
    room1.addChest(6, 0, 10);
    room1.addChest(10, 0, 30);
    // Создаем игровое поле на основе созданной комнаты
    Game game(room1.getWidth(), room1.getHeight());
    game.setCurrentRoom(room1);
    // Основной цикл игры
    while (true) { // в отдельный метод
        game.render();
    }
    return 0;
}