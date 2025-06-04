#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "Pipe.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleCollisions();
    void spawnPipes();
    void resetGame();

    sf::RenderWindow mWindow;
    sf::Texture mBackgroundTexture;
    sf::Sprite mBackground;

    Bird mBird;
    std::vector<Pipe> mPipes;
    sf::Clock mPipeClock;
    sf::Clock mGameClock;

    int mScore;
    sf::Font mFont;
    sf::Text mScoreText;
    sf::Text mGameOverText;

    bool mGameOver;
};

#endif // GAME_H