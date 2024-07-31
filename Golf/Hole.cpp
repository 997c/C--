#include "Hole.h"

Hole::Hole(float x, float y) : x(x), y(y), radius(15) {}

void Hole::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { static_cast<int>(x - radius), static_cast<int>(y - radius), static_cast<int>(radius * 2), static_cast<int>(radius * 2) };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}