#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Board.h"

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
    Board board;
};

#endif // GAME_H