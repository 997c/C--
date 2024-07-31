#include "Board.h"

Board::Board() : grid(3, std::vector<char>(3, ' ')), currentPlayer('X') {}

void Board::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 1; i < 3; ++i) {
        SDL_RenderDrawLine(renderer, i * 100, 0, i * 100, 300);
        SDL_RenderDrawLine(renderer, 0, i * 100, 300, i * 100);
    }

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (grid[y][x] == 'X') {
                drawX(renderer, x, y);
            } else if (grid[y][x] == 'O') {
                drawO(renderer, x, y);
            }
        }
    }
}

void Board::handleClick(int x, int y) {
    int gridX = x / 100;
    int gridY = y / 100;

    if (grid[gridY][gridX] == ' ') {
        grid[gridY][gridX] = currentPlayer;
        if (checkWin()) {
            SDL_Log("Player %c wins!\n", currentPlayer);
            grid = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        } else if (checkDraw()) {
            SDL_Log("Draw!\n");
            grid = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

bool Board::checkWin() {
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) return true;
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) return true;
    }
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) return true;
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) return true;
    return false;
}

bool Board::checkDraw() {
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

void Board::drawX(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x * 100, y * 100, (x + 1) * 100, (y + 1) * 100);
    SDL_RenderDrawLine(renderer, x * 100, (y + 1) * 100, (x + 1) * 100, y * 100);
}

void Board::drawO(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(renderer, x * 100 + 10, y * 100 + 10, (x + 1) * 100 - 10, y * 100 + 10);
    SDL_RenderDrawLine(renderer, (x + 1) * 100 - 10, y * 100 + 10, (x + 1) * 100 - 10, (y + 1) * 100 - 10);
    SDL_RenderDrawLine(renderer, (x + 1) * 100 - 10, (y + 1) * 100 - 10, x * 100 + 10, (y + 1) * 100 - 10);
    SDL_RenderDrawLine(renderer, x * 100 + 10, (y + 1) * 100 - 10, x * 100 + 10, y * 100 + 10);
}