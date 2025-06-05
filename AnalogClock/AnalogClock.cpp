#include "AnalogClock.h"
#include <cmath>
#include <ctime>

AnalogClock::AnalogClock(float radius, const sf::Vector2f& position) 
    : m_position(position), 
      m_radius(radius),
      m_hourHand(radius * 0.5f, radius * 0.03f, sf::Color::Black),
      m_minuteHand(radius * 0.8f, radius * 0.02f, sf::Color::Black),
      m_secondHand(radius * 0.9f, radius * 0.01f, sf::Color::Red) {
    
    createClockFace();
    createClockHands();
}

void AnalogClock::update() {
    updateClockHands();
}

void AnalogClock::draw(sf::RenderWindow& window) const {
    window.draw(m_face);
    
    for (const auto& mark : m_hourMarks) {
        window.draw(mark);
    }
    
    for (const auto& mark : m_minuteMarks) {
        window.draw(mark);
    }
    
    window.draw(m_hourHand.getShape());
    window.draw(m_minuteHand.getShape());
    window.draw(m_secondHand.getShape());
    window.draw(m_center);
}

void AnalogClock::setPosition(const sf::Vector2f& position) {
    m_position = position;
    m_face.setPosition(position);
    m_center.setPosition(position);
    
    m_hourHand.setPosition(position);
    m_minuteHand.setPosition(position);
    m_secondHand.setPosition(position);
    
    // Update marks positions
    for (auto& mark : m_hourMarks) {
        sf::FloatRect bounds = mark.getLocalBounds();
        mark.setOrigin(bounds.width / 2, bounds.height / 2);
        mark.setPosition(position);
    }
    
    for (auto& mark : m_minuteMarks) {
        sf::FloatRect bounds = mark.getLocalBounds();
        mark.setOrigin(bounds.width / 2, bounds.height / 2);
        mark.setPosition(position);
    }
}

void AnalogClock::createClockFace() {
    m_face.setRadius(m_radius);
    m_face.setFillColor(sf::Color(240, 240, 240));
    m_face.setOutlineThickness(m_radius * 0.02f);
    m_face.setOutlineColor(sf::Color::Black);
    m_face.setOrigin(m_radius, m_radius);
    m_face.setPosition(m_position);
    
    m_center.setRadius(m_radius * 0.03f);
    m_center.setFillColor(sf::Color::Black);
    m_center.setOrigin(m_center.getRadius(), m_center.getRadius());
    m_center.setPosition(m_position);
    
    // Create hour marks
    for (int i = 0; i < 12; ++i) {
        sf::RectangleShape mark(sf::Vector2f(m_radius * 0.02f, m_radius * 0.1f));
        mark.setFillColor(sf::Color::Black);
        
        float angle = i * 30.0f;
        float x = m_radius * 0.85f * std::sin(angle * 3.14159265f / 180.0f);
        float y = -m_radius * 0.85f * std::cos(angle * 3.14159265f / 180.0f);
        
        mark.setPosition(m_position.x + x, m_position.y + y);
        mark.setRotation(angle);
        
        m_hourMarks.push_back(mark);
    }
    
    // Create minute marks
    for (int i = 0; i < 60; ++i) {
        if (i % 5 == 0) continue; // Skip positions where hour marks are
        
        sf::RectangleShape mark(sf::Vector2f(m_radius * 0.01f, m_radius * 0.05f));
        mark.setFillColor(sf::Color::Black);
        
        float angle = i * 6.0f;
        float x = m_radius * 0.9f * std::sin(angle * 3.14159265f / 180.0f);
        float y = -m_radius * 0.9f * std::cos(angle * 3.14159265f / 180.0f);
        
        mark.setPosition(m_position.x + x, m_position.y + y);
        mark.setRotation(angle);
        
        m_minuteMarks.push_back(mark);
    }
}

void AnalogClock::createClockHands() {
    m_hourHand.setPosition(m_position);
    m_minuteHand.setPosition(m_position);
    m_secondHand.setPosition(m_position);
    
    updateClockHands();
}

void AnalogClock::updateClockHands() {
    // Get current time
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    
    // Calculate angles
    float hourAngle = (localTime->tm_hour % 12) * 30.0f + localTime->tm_min * 0.5f;
    float minuteAngle = localTime->tm_min * 6.0f;
    float secondAngle = localTime->tm_sec * 6.0f;
    
    // Set rotations
    m_hourHand.setRotation(hourAngle);
    m_minuteHand.setRotation(minuteAngle);
    m_secondHand.setRotation(secondAngle);
}