#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class SpiderMan {
public:
    SpiderMan(SDL_Renderer* renderer, int initialX, int initialY);
    ~SpiderMan();

    void handleInput(SDL_Event& event);
    void update();
    void render();

private:
    SDL_Texture* texture;
    SDL_Rect position;
    int velocityX;
    int velocityY;
    int frame;
    int frameDelay;
};
