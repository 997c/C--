#ifndef PADDLE_H
#define PADDLE_H

#include <SDL.h>

class Paddle {
public:
    Paddle(int x, int y);
    void moveUp();
    void moveDown();
    void moveTo(int y);
    void render(SDL_Renderer* renderer);
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int x, y;
    int width, height;
    int speed;
};

#endif // PADDLE_H