#include "Game.h"

Game::Game() : running(false), ball(400, 500), hole(400, 100), aiming(false), power(0) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Golf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
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
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                aiming = true;
            }
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                aiming = false;
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                ball.setVelocity((mouseX - ball.getX()) * power, (mouseY - ball.getY()) * power);
                power = 0;
            }
        }
    }
}

void Game::update() {
    if (aiming) {
        power += 0.01f;
        if (power > 1.0f) {
            power = 1.0f;
        }
    } else {
        ball.update();
        if (ball.collidesWith(hole)) {
            SDL_Log("Hole in one!\n");
            ball.reset();
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    ball.render(renderer);
    hole.render(renderer);

    SDL_RenderPresent(renderer);
}