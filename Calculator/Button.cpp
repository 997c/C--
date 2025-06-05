#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, 
               const std::string& value, const sf::Font& font) 
    : value(value) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color(70, 70, 70));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(100, 100, 100));

    text.setFont(font);
    text.setString(value);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(position.x + size.x/2.0f,
                     position.y + size.y/2.0f);
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(text);
}

bool Button::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

const std::string& Button::getValue() const {
    return value;
}