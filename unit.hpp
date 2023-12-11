#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
#endif
#include <iostream>
using namespace std;
#pragma once

class Unit {
public:
    SDL_Rect srcRect, moverRect;
    bool operator==(const Unit& u1) const;
};

