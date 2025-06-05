#include "snake.h"
#include <iostream>

Snake::Snake(int startX, int startY) 
    : x(startX), y(startY), dir(Direction::RIGHT), tailLength(0) {}

void Snake::move() {
    // Move tail segments
    if (tailLength > 0) {
        if (tail.size() >= tailLength) {
            tail.erase(tail.begin());
        }
        tail.push_back({x, y});
    }
    
    // Move head
    switch (dir) {
    case Direction::LEFT:
        x--;
        break;
    case Direction::RIGHT:
        x++;
        break;
    case Direction::UP:
        y--;
        break;
    case Direction::DOWN:
        y++;
        break;
    default:
        break;
    }
}

void Snake::grow() {
    tailLength++;
}

void Snake::setDirection(Direction newDir) {
    // Prevent 180-degree turns
    if ((dir == Direction::LEFT && newDir != Direction::RIGHT) ||
        (dir == Direction::RIGHT && newDir != Direction::LEFT) ||
        (dir == Direction::UP && newDir != Direction::DOWN) ||
        (dir == Direction::DOWN && newDir != Direction::UP)) {
        dir = newDir;
    }
}

int Snake::getX() const {
    return x;
}

int Snake::getY() const {
    return y;
}

const std::vector<Segment>& Snake::getTail() const {
    return tail;
}

void Snake::draw() const {
    // Drawing is handled by Game class
}