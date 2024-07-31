#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "Paddle.h"

class Ball {
public:
    Ball(int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    void bounce();
    void reset();
    bool collidesWith(const Paddle& paddle) const;
    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
    int width, height;
    int speedX, speedY;
};

#endif // BALL_H