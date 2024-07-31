#include "Ball.h"

Ball::Ball(int x, int y) : x(x), y(y), width(20), height(20), speedX(5), speedY(5) {}

void Ball::update() {
    x += speedX;
    y += speedY;
    if (y < 0 || y + height > 600) {
        speedY = -speedY;
    }
}

void Ball::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::bounce() {
    speedX = -speedX;
}

void Ball::reset() {
    x = 400;
    y = 300;
    speedX = -speedX;
}

bool Ball::collidesWith(const Paddle& paddle) const {
    return x < paddle.getX() + paddle.getWidth() &&
           x + width > paddle.getX() &&
           y < paddle.getY() + paddle.getHeight() &&
           y + height > paddle.getY();
}