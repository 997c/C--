#include "ClockHand.h"

ClockHand::ClockHand(float length, float thickness, const sf::Color& color) 
    : m_length(length), m_thickness(thickness) {
    m_shape.setSize(sf::Vector2f(m_thickness, m_length));
    m_shape.setFillColor(color);
    m_shape.setOrigin(m_thickness / 2.0f, m_length);
}

void ClockHand::setRotation(float angle) {
    m_shape.setRotation(angle);
}

void ClockHand::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
}

void ClockHand::setLength(float length) {
    m_length = length;
    m_shape.setSize(sf::Vector2f(m_thickness, m_length));
    m_shape.setOrigin(m_thickness / 2.0f, m_length);
}

const sf::RectangleShape& ClockHand::getShape() const {
    return m_shape;
}