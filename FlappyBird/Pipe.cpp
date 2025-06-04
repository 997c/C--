#include "Pipe.h"
#include <cstdlib>
#include <ctime>

Pipe::Pipe(float windowWidth, float windowHeight) : 
    mSpeed(-150.0f),
    mPassed(false)
{
    // Seed random number generator
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }

    if (!mTopPipeTexture.loadFromFile("assets/pipe_top.png")) {
        // Handle error
    }
    if (!mBottomPipeTexture.loadFromFile("assets/pipe_bottom.png")) {
        // Handle error
    }

    mTopPipe.setTexture(mTopPipeTexture);
    mBottomPipe.setTexture(mBottomPipeTexture);

    // Scale pipes to fit window
    float scale = windowWidth / mTopPipeTexture.getSize().x;
    mTopPipe.setScale(scale, scale);
    mBottomPipe.setScale(scale, scale);

    // Random gap position
    float gapPosition = std::rand() % static_cast<int>(windowHeight * 0.6f) + windowHeight * 0.2f;
    float gapSize = 150.0f;

    mTopPipe.setPosition(windowWidth, gapPosition - gapSize - mTopPipe.getGlobalBounds().height);
    mBottomPipe.setPosition(windowWidth, gapPosition + gapSize);
}

void Pipe::update() {
    mTopPipe.move(mSpeed * 0.016f, 0); // Assuming ~60 FPS
    mBottomPipe.move(mSpeed * 0.016f, 0);
}

void Pipe::draw(sf::RenderWindow& window) {
    window.draw(mTopPipe);
    window.draw(mBottomPipe);
}

bool Pipe::intersects(const sf::FloatRect& bounds) const {
    return mTopPipe.getGlobalBounds().intersects(bounds) || 
           mBottomPipe.getGlobalBounds().intersects(bounds);
}

float Pipe::getRightBound() const {
    return mTopPipe.getPosition().x + mTopPipe.getGlobalBounds().width;
}

void Pipe::setPassed(bool passed) {
    mPassed = passed;
}

bool Pipe::isPassed() const {
    return mPassed;
}