#ifndef HOLE_H
#define HOLE_H

#include <SDL.h>

class Hole {
public:
    Hole(float x, float y);
    void render(SDL_Renderer* renderer);
    float getX() const { return x; }
    float getY() const { return y; }
    float getRadius() const { return radius; }

private:
    float x, y;
    float radius;
};

#endif // HOLE_H