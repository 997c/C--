#include <SFML/Graphics.hpp>
#include "AnalogClock.h"

int main() {
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Analog Clock");
    window.setFramerateLimit(60);
    
    // Create clock centered in the window
    float clockRadius = std::min(windowWidth, windowHeight) * 0.4f;
    AnalogClock clock(clockRadius, sf::Vector2f(windowWidth / 2.0f, windowHeight / 2.0f));
    
    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        // Update clock
        clock.update();
        
        // Draw
        window.clear(sf::Color::White);
        clock.draw(window);
        window.display();
    }
    
    return 0;
}