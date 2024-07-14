#include "Snake.h"
#include "Food.h"
#include <iostream>

Snake::Snake() : direction(Direction::RIGHT) {
    body.push_back({ 10, 10 });
}
void Snake::setDirection(Direction newDirection) {
    direction = newDirection;
}
void Snake::move() {
    // Move the snake based on the current direction
    std::pair<int, int> newHead = body.front();
    switch (direction) {
    case Direction::UP: newHead.second--; break;
    case Direction::DOWN: newHead.second++; break;
    case Direction::LEFT: newHead.first--; break;
    case Direction::RIGHT: newHead.first++; break;
    }
    body.insert(body.begin(), newHead);
    body.pop_back();
}
bool Snake::checkCollision() {
    // Check for collision with walls or self
    std::pair<int, int> head = body.front();
    if (head.first < 0 || head.first >= 20 || head.second < 0 || head.second >= 20) {
        return true;
    }
    for (int i = 1; i < body.size(); ++i) {
        if (body[i] == head) {
            return true;
        }
    }
    return false;
}
bool Snake::eatFood(const Food& food) {
    if (body.front() == food.getPosition()) {
        body.push_back(body.back()); // Grow the snake
        return true;
    }
    return false;
}
const std::vector<std::pair<int, int>>& Snake::getBody() const {
    return body;
}
void Snake::render() {
    for (const auto& segment : body) {
        std::cout << "O"; // Print snake segment
    }
}
