#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include <vector>

class Board {
public:
    Board();
    void render(SDL_Renderer* renderer);
    void handleClick(int x, int y);

private:
    std::vector<std::vector<char>> grid;
    char currentPlayer;
    bool checkWin();
    bool checkDraw();
    void drawX(SDL_Renderer* renderer, int x, int y);
    void drawO(SDL_Renderer* renderer, int x, int y);
};

#endif // BOARD_H