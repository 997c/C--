#include "Paddle.h"

Paddle::Paddle(int x, int y) : x(x), y(y), width(20), height(100), speed(10) {}

void Paddle::moveUp() {
    y = (y - speed < 0) ? 0 : y - speed;
}

void Paddle::moveDown() {
    y = (y + speed + height > 600) ? 600 - height : y + speed;
}

void Paddle::moveTo(int targetY) {
    if (targetY < y + height / 2) {
        moveUp();
    } else if (targetY > y + height / 2) {
        moveDown();
    }
}

void Paddle::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}