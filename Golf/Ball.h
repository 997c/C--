#ifndef BALL_H
#define BALL_H

#include <SDL.h>

class Ball {
public:
    Ball(float x, float y);
    void render(SDL_Renderer* renderer);
    void update();
    void setVelocity(float vx, float vy);
    float getX() const { return x; }
    float getY() const { return y; }
    void reset();
    bool collidesWith(const class Hole& hole) const;

private:
    float x, y;
    float vx, vy;
    float radius;
};

#endif // BALL_H