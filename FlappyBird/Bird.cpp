#include "Bird.h"

Bird::Bird() : 
    mVelocity(0.0f),
    mGravity(500.0f),
    mFlapStrength(-200.0f)
{
    if (!mTexture.loadFromFile("assets/bird.png")) {
        // Handle error
    }
    mSprite.setTexture(mTexture);
    mSprite.setPosition(100, 300);
    mSprite.setScale(0.05f, 0.05f);
}

void Bird::update() {
    // Apply gravity
    mVelocity += mGravity * 0.016f; // Assuming ~60 FPS
    mSprite.move(0, mVelocity * 0.016f);
}

void Bird::draw(sf::RenderWindow& window) {
    window.draw(mSprite);
}

void Bird::flap() {
    mVelocity = mFlapStrength;
}

void Bird::reset() {
    mSprite.setPosition(100, 300);
    mVelocity = 0.0f;
}

sf::Vector2f Bird::getPosition() const {
    return mSprite.getPosition();
}

sf::FloatRect Bird::getBounds() const {
    return mSprite.getGlobalBounds();
}

float Bird::getLeftBound() const {
    return mSprite.getPosition().x + mSprite.getGlobalBounds().width;
}