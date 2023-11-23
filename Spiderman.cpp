#include "SpiderMan.hpp"

SpiderMan::SpiderMan(SDL_Renderer* renderer, int initialX, int initialY) {
    // Load Spider-Man texture
    SDL_Surface* surface = IMG_Load("spiderman.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Set initial position
    position.x = initialX;
    position.y = initialY;
    position.w = 50; // Adjust as needed
    position.h = 50; // Adjust as needed

    // Set initial velocity
    velocityX = 0;
    velocityY = 0;

    // Initialize animation variables
    frame = 0;
    frameDelay = 5; // Adjust as needed
}

SpiderMan::~SpiderMan() {
    SDL_DestroyTexture(texture);
}

void SpiderMan::handleInput(SDL_Event& event) {
    // Handle input to control Spider-Man's movement
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                velocityX = -5;
                break;
            case SDLK_RIGHT:
                velocityX = 5;
                break;
            case SDLK_UP:
                velocityY = -5;
                break;
            case SDLK_DOWN:
                velocityY = 5;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_RIGHT:
                velocityX = 0;
                break;
            case SDLK_UP:
            case SDLK_DOWN:
                velocityY = 0;
                break;
        }
    }
}

void SpiderMan::update() {
    // Update Spider-Man's position and animation
    position.x += velocityX;
    position.y += velocityY;

    // Animation logic (change frames after a delay)
    frameDelay--;
    if (frameDelay <= 0) {
        frame = (frame + 1) % 4; // Assuming 4 frames in the sprite sheet
        frameDelay = 5; // Reset the frame delay
    }
}

void SpiderMan::render() {
    // Render Spider-Man
    SDL_Rect srcRect = { frame * 50, 0, 50, 50 }; // Assuming each frame is 50x50
    SDL_RenderCopy(renderer, texture, &srcRect, &position);
}
