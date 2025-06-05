#ifndef FOOD_H
#define FOOD_H

#include "snake.h"
#include <random>

class Food {
public:
    Food();
    void generate(int width, int height, const Snake& snake);
    int getX() const;
    int getY() const;
    void draw() const;

private:
    int x, y;
};

#endif // FOOD_H