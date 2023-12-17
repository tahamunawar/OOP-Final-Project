#include "unit.hpp"
#pragma once

class Projectile : public Unit

{
    private:
    int movingSpeed=0, damageDealt = 0;
    const char* imgPath;
    bool markedForDeletion;
    public:
    Projectile(SDL_Renderer* _renderer, const char *, const char *, int=0, int=0);
    ~Projectile();
    SDL_Texture* projectileTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    void render();
    void move();
    // void setMovingSpeed(int);
    // void setDamageDealt(int);
    void markForDeletion();
    bool isMarkedForDeletion();
};