#include "Game.h"
#include <iostream>
#include <sstream>

Game::Game() : 
    mWindow(sf::VideoMode(400, 600), "Flappy Bird"),
    mBird(),
    mScore(0),
    mGameOver(false)
{
    // Load background
    if (!mBackgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "Could not load background texture" << std::endl;
    }
    mBackground.setTexture(mBackgroundTexture);

    // Load font
    if (!mFont.loadFromFile("assets/flappy.ttf")) {
        std::cerr << "Could not load font" << std::endl;
    }

    // Setup score text
    mScoreText.setFont(mFont);
    mScoreText.setCharacterSize(30);
    mScoreText.setFillColor(sf::Color::White);
    mScoreText.setPosition(10, 10);

    // Setup game over text
    mGameOverText.setFont(mFont);
    mGameOverText.setCharacterSize(40);
    mGameOverText.setFillColor(sf::Color::Red);
    mGameOverText.setString("GAME OVER\nPress R to restart");
    mGameOverText.setPosition(100, 250);
}

void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        if (!mGameOver) {
            update();
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space && !mGameOver) {
                mBird.flap();
            }
            if (event.key.code == sf::Keyboard::R && mGameOver) {
                resetGame();
            }
        }
    }
}

void Game::update() {
    mBird.update();

    // Spawn new pipes
    if (mPipeClock.getElapsedTime().asSeconds() > 2.0f) {
        spawnPipes();
        mPipeClock.restart();
    }

    // Update pipes
    for (auto& pipe : mPipes) {
        pipe.update();

        // Check if bird passed the pipe
        if (!pipe.isPassed() && pipe.getRightBound() < mBird.getLeftBound()) {
            pipe.setPassed(true);
            mScore++;
            std::stringstream ss;
            ss << mScore;
            mScoreText.setString(ss.str());
        }
    }

    // Remove pipes that are off screen
    mPipes.erase(std::remove_if(mPipes.begin(), mPipes.end(), 
        [](const Pipe& pipe) { return pipe.getRightBound() < 0; }), 
        mPipes.end());

    handleCollisions();
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mBackground);

    for (const auto& pipe : mPipes) {
        pipe.draw(mWindow);
    }

    mBird.draw(mWindow);
    mWindow.draw(mScoreText);

    if (mGameOver) {
        mWindow.draw(mGameOverText);
    }

    mWindow.display();
}

void Game::handleCollisions() {
    // Check if bird hits the ground or ceiling
    if (mBird.getPosition().y < 0 || mBird.getPosition().y > mWindow.getSize().y) {
        mGameOver = true;
    }

    // Check collisions with pipes
    for (const auto& pipe : mPipes) {
        if (pipe.intersects(mBird.getBounds())) {
            mGameOver = true;
            break;
        }
    }
}

void Game::spawnPipes() {
    mPipes.emplace_back(mWindow.getSize().x, mWindow.getSize().y);
}

void Game::resetGame() {
    mBird.reset();
    mPipes.clear();
    mScore = 0;
    mScoreText.setString("0");
    mGameOver = false;
    mPipeClock.restart();
}