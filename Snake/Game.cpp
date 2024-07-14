#include "Game.h"
#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds

Game::Game() : gameOver(false), snake(), food() {}
void Game::run() {
    while (!gameOver) {
        processInput();
        update();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Control the speed of the game
    }
}
void Game::processInput() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w': snake.setDirection(Direction::UP); break;
        case 's': snake.setDirection(Direction::DOWN); break;
        case 'a': snake.setDirection(Direction::LEFT); break;
        case 'd': snake.setDirection(Direction::RIGHT); break;
        case 'q': gameOver = true; break;
        }
    }
}
void Game::update() {
    snake.move();
    if (snake.checkCollision()) {
        gameOver = true;
    }
    if (snake.eatFood(food)) {
        food.respawn();
    }
}
void Game::render() {
    const int width = 20;
    const int height = 20;
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));
    for (const auto& segment : snake.getBody()) {
        grid[segment.second][segment.first] = 'O';
    }
    auto foodPos = food.getPosition();
    grid[foodPos.second][foodPos.first] = 'F';
    system("cls"); // Clear the screen
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}
