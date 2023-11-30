#include "healthpowerup.hpp"

HealthPowerUp::HealthPowerUp(SDL_Renderer* _renderer, int x, int y)
{
    renderer = _renderer;
    healthPowerUpTexture = IMG_LoadTexture(renderer, "medkit.png");
    if (healthPowerUpTexture == nullptr) 
    {
        cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
        SDL_DestroyTexture(healthPowerUpTexture);
    }
    srcRect = {432,468,252,216};
    moverRect = {x,y,100,100};
}

void HealthPowerUp::render()
{
    SDL_RenderCopy(renderer, healthPowerUpTexture, &srcRect, &moverRect);
}

void HealthPowerUp::applyPowerUp(){}