#include "game.h"
#include <iostream>

Game::Game() : width(50), height(25), score(0), isRunning(true), snake(width/2, height/2) {
    init();
}

Game::~Game() {}

void Game::init() {
    food.generate(width, height, snake);
}

void Game::run() {
    while (isRunning) {
        draw();
        input();
        logic();
        Sleep(100); // Control game speed
    }
}

void Game::draw() {
    system("cls"); // Clear screen
    drawBorder();
    snake.draw();
    food.draw();
    drawScore();
}

void Game::drawBorder() {
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "#";
            
            if (i == snake.getY() && j == snake.getX())
                std::cout << "O";
            else if (i == food.getY() && j == food.getX())
                std::cout << "F";
            else {
                bool isTail = false;
                for (auto segment : snake.getTail()) {
                    if (segment.x == j && segment.y == i) {
                        std::cout << "o";
                        isTail = true;
                        break;
                    }
                }
                if (!isTail)
                    std::cout << " ";
            }

            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
}

void Game::drawScore() {
    std::cout << "Score: " << score << std::endl;
}

void Game::input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            snake.setDirection(Direction::LEFT);
            break;
        case 'd':
            snake.setDirection(Direction::RIGHT);
            break;
        case 'w':
            snake.setDirection(Direction::UP);
            break;
        case 's':
            snake.setDirection(Direction::DOWN);
            break;
        case 'x':
            isRunning = false;
            break;
        }
    }
}

void Game::logic() {
    snake.move();
    
    // Check collision with food
    if (snake.getX() == food.getX() && snake.getY() == food.getY()) {
        score += 10;
        food.generate(width, height, snake);
        snake.grow();
    }
    
    // Check collision with walls
    if (snake.getX() < 0 || snake.getX() >= width || 
        snake.getY() < 0 || snake.getY() >= height) {
        gameOver();
    }
    
    // Check collision with tail
    for (auto segment : snake.getTail()) {
        if (snake.getX() == segment.x && snake.getY() == segment.y) {
            gameOver();
        }
    }
}

void Game::gameOver() {
    system("cls");
    std::cout << "Game Over!" << std::endl;
    std::cout << "Final Score: " << score << std::endl;
    isRunning = false;
}