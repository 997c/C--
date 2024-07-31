#include "Ball.h"
#include "Hole.h"

Ball::Ball(float x, float y) : x(x), y(y), vx(0), vy(0), radius(10) {}

void Ball::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { static_cast<int>(x - radius), static_cast<int>(y - radius), static_cast<int>(radius * 2), static_cast<int>(radius * 2) };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::update() {
    x += vx;
    y += vy;
    if (x - radius < 0 || x + radius > 800) {
        vx = -vx;
    }
    if (y - radius < 0 || y + radius > 600) {
        vy = -vy;
    }
}

void Ball::setVelocity(float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
}

void Ball::reset() {
    x = 400;
    y = 500;
    vx = 0;
    vy = 0;
}

bool Ball::collidesWith(const Hole& hole) const {
    float dx = x - hole.getX();
    float dy = y - hole.getY();
    float distance = sqrt(dx * dx + dy * dy);
    return distance < radius + hole.getRadius();
}