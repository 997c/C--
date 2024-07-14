#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <utility> // for std::pair
class Food; // Forward declaration
enum class Direction { UP, DOWN, LEFT, RIGHT };
class Snake {
public:
    Snake();
    void setDirection(Direction newDirection);
    void move();
    bool checkCollision();
    bool eatFood(const Food& food);
    void render(); // Optionally keep for individual rendering
    const std::vector<std::pair<int, int>>& getBody() const; // Add this getter
private:
    std::vector<std::pair<int, int>> body;
    Direction direction;
};
#endif
