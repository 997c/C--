#include "Calculator.h"

int main() {
    // Silence all SFML errors
    sf::err().rdbuf(nullptr);
    
    try {
        Calculator calculator;
        calculator.run();
    } catch (...) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}