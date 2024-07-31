#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Paddle.h"
#include "Ball.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    Paddle playerPaddle;
    Paddle aiPaddle;
    Ball ball;
};

#endif // GAME_H