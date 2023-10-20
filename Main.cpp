#include <iostream>
#include <vector>

#include "Cell.h"
#include "GameFild.h"

using namespace std;

int main(){
    // Создаем объект игры
    Game game(20, 10);

    // Основной цикл игры
    while (true) {
        game.render();
    }
    return 0;
}