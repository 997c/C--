#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include <conio.h>
#include <windows.h>

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void init();
    void draw();
    void input();
    void logic();
    void gameOver();
    void drawBorder();
    void drawScore();

    bool isRunning;
    int width, height;
    int score;
    Snake snake;
    Food food;
};

#endif // GAME_H