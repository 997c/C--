#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <iostream>

const float PI = 3.14159265358979323846f;

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(400, 400), "Analog Clock");
    window.setFramerateLimit(60);

    // Clock face
    sf::CircleShape clockFace(150.f);
    clockFace.setFillColor(sf::Color::White);
    clockFace.setOutlineThickness(2.f);
    clockFace.setOutlineColor(sf::Color::Black);
    clockFace.setPosition(50.f, 50.f);

    // Clock hands
    sf::RectangleShape hourHand(sf::Vector2f(80.f, 6.f));
    hourHand.setFillColor(sf::Color::Black);
    hourHand.setOrigin(0.f, 3.f);

    sf::RectangleShape minuteHand(sf::Vector2f(120.f, 4.f));
    minuteHand.setFillColor(sf::Color::Blue);
    minuteHand.setOrigin(0.f, 2.f);

    sf::RectangleShape secondHand(sf::Vector2f(140.f, 2.f));
    secondHand.setFillColor(sf::Color::Red);
    secondHand.setOrigin(0.f, 1.f);

    // Center point
    sf::CircleShape centerPoint(5.f);
    centerPoint.setFillColor(sf::Color::Red);
    centerPoint.setOrigin(5.f, 5.f);

    // Clock numbers
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font. Using default." << std::endl;
    }
    sf::Text numbers[12];
    for (int i = 0; i < 12; ++i) {
        numbers[i].setFont(font);
        numbers[i].setString(std::to_string(i + 1));
        numbers[i].setCharacterSize(20);
        numbers[i].setFillColor(sf::Color::Black);
        
        float angle = i * 30.f * PI / 180.f;
        float radius = 120.f;
        numbers[i].setPosition(200.f + radius * std::sin(angle) - 5.f, 
                              200.f - radius * std::cos(angle) - 10.f);
    }

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get current time
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);
        
        int hours = localTime->tm_hour % 12;
        int minutes = localTime->tm_min;
        int seconds = localTime->tm_sec;

        // Calculate angles
        float hourAngle = (hours * 30.f + minutes * 0.5f) * PI / 180.f;
        float minuteAngle = minutes * 6.f * PI / 180.f;
        float secondAngle = seconds * 6.f * PI / 180.f;

        // Position hands
        hourHand.setPosition(200.f, 200.f);
        hourHand.setRotation(hourAngle * 180.f / PI);

        minuteHand.setPosition(200.f, 200.f);
        minuteHand.setRotation(minuteAngle * 180.f / PI);

        secondHand.setPosition(200.f, 200.f);
        secondHand.setRotation(secondAngle * 180.f / PI);

        centerPoint.setPosition(200.f, 200.f);

        // Draw everything
        window.clear(sf::Color(240, 240, 240));
        window.draw(clockFace);
        
        for (int i = 0; i < 12; ++i) {
            window.draw(numbers[i]);
        }
        
        window.draw(hourHand);
        window.draw(minuteHand);
        window.draw(secondHand);
        window.draw(centerPoint);
        
        window.display();
    }

    return 0;
}