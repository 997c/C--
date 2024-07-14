#include "Food.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Food::Food() {
    std::srand(std::time(0));
    respawn();
}
void Food::respawn() {
    position.first = std::rand() % 20;
    position.second = std::rand() % 20;
}
std::pair<int, int> Food::getPosition() const {
    return position;
}
void Food::render() {
    std::cout << "F"; // Print food
}
