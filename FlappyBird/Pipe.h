#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>

class Pipe {
public:
    Pipe(float windowWidth, float windowHeight);
    void update();
    void draw(sf::RenderWindow& window);
    bool intersects(const sf::FloatRect& bounds) const;
    float getRightBound() const;
    void setPassed(bool passed);
    bool isPassed() const;

private:
    sf::Texture mTopPipeTexture;
    sf::Texture mBottomPipeTexture;
    sf::Sprite mTopPipe;
    sf::Sprite mBottomPipe;
    float mSpeed;
    bool mPassed;
};

#endif // PIPE_H