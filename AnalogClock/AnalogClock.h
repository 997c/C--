#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <SFML/Graphics.hpp>
#include "ClockHand.h"

class AnalogClock {
public:
    AnalogClock(float radius, const sf::Vector2f& position);
    
    void update();
    void draw(sf::RenderWindow& window) const;
    void setPosition(const sf::Vector2f& position);
    
private:
    void createClockFace();
    void createClockHands();
    void updateClockHands();
    
    sf::Vector2f m_position;
    float m_radius;
    
    sf::CircleShape m_face;
    sf::CircleShape m_center;
    
    ClockHand m_hourHand;
    ClockHand m_minuteHand;
    ClockHand m_secondHand;
    
    std::vector<sf::RectangleShape> m_hourMarks;
    std::vector<sf::RectangleShape> m_minuteMarks;
};

#endif // ANALOGCLOCK_H