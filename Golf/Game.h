#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Ball.h"
#include "Hole.h"

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
    Ball ball;
    Hole hole;
    bool aiming;
    float power;
};

#endif // GAME_H