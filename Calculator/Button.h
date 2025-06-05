#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, 
           const std::string& value, const sf::Font& font);
    
    void draw(sf::RenderWindow& window) const;
    bool contains(const sf::Vector2f& point) const;
    const std::string& getValue() const;

private:
    sf::RectangleShape shape;
    sf::Text text;
    std::string value;
};

#endif // BUTTON_H