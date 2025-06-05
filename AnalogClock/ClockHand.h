#ifndef CLOCKHAND_H
#define CLOCKHAND_H

#include <SFML/Graphics.hpp>

class ClockHand {
public:
    ClockHand(float length, float thickness, const sf::Color& color);
    
    void setRotation(float angle);
    void setPosition(const sf::Vector2f& position);
    void setLength(float length);
    
    const sf::RectangleShape& getShape() const;

private:
    sf::RectangleShape m_shape;
    float m_length;
    float m_thickness;
};

#endif // CLOCKHAND_H