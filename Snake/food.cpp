#include "food.h"
#include <ctime>

Food::Food() : x(0), y(0) {
    std::srand(std::time(nullptr));
}

void Food::generate(int width, int height, const Snake& snake) {
    bool validPosition = false;
    
    while (!validPosition) {
        x = std::rand() % width;
        y = std::rand() % height;
        
        // Check if food appears on snake
        if (x != snake.getX() || y != snake.getY()) {
            bool onTail = false;
            for (auto segment : snake.getTail()) {
                if (x == segment.x && y == segment.y) {
                    onTail = true;
                    break;
                }
            }
            if (!onTail) {
                validPosition = true;
            }
        }
    }
}

int Food::getX() const {
    return x;
}

int Food::getY() const {
    return y;
}

void Food::draw() const {
    // Drawing is handled by Game class
}