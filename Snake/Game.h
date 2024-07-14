#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
class Game {
public:
    Game();
    void run();
private:
    void processInput();
    void update();
    void render();
    Snake snake;
    Food food;
    bool gameOver;
};
#endif
