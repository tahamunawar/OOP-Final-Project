#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif
#include <iostream>
#include <cstring>
using namespace std;
#pragma once

class Unit {
public:
    SDL_Rect srcRect, moverRect;
    SDL_Rect getMoverRect() const;
};

