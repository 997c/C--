#include "Game.h"

Game::Game() : running(false), playerPaddle(10, 150), aiPaddle(770, 150), ball(400, 300) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        if (!window) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            } else {
                running = true;
            }
        }
    }
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16); // ~60 FPS
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]) {
        playerPaddle.moveUp();
    }
    if (state[SDL_SCANCODE_DOWN]) {
        playerPaddle.moveDown();
    }
}

void Game::update() {
    aiPaddle.moveTo(ball.getY());
    ball.update();
    if (ball.collidesWith(playerPaddle) || ball.collidesWith(aiPaddle)) {
        ball.bounce();
    }
    if (ball.getX() < 0 || ball.getX() > 800) {
        ball.reset();
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    playerPaddle.render(renderer);
    aiPaddle.render(renderer);
    ball.render(renderer);

    SDL_RenderPresent(renderer);
}