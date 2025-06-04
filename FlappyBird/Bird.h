#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>

class Bird {
public:
    Bird();
    void update();
    void draw(sf::RenderWindow& window);
    void flap();
    void reset();
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    float getLeftBound() const;

private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    float mVelocity;
    float mGravity;
    float mFlapStrength;
};

#endif // BIRD_H