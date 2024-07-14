#ifndef FOOD_H
#define FOOD_H

#include <utility>
class Food {
public:
    Food();
    void respawn();
    std::pair<int, int> getPosition() const;
    void render();
private:
    std::pair<int, int> position;
};
#endif
