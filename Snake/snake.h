#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

enum class Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct Segment {
    int x, y;
};

class Snake {
public:
    Snake(int startX, int startY);
    
    void move();
    void grow();
    void setDirection(Direction newDir);
    int getX() const;
    int getY() const;
    const std::vector<Segment>& getTail() const;
    void draw() const;

private:
    int x, y;
    Direction dir;
    std::vector<Segment> tail;
    int tailLength;
};

#endif // SNAKE_H