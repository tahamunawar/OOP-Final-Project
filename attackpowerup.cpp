#include "attackpowerup.hpp"

AttackPowerUp::AttackPowerUp(SDL_Renderer* _renderer, int x, int y)
{
    renderer = _renderer;
    attackPowerUpTexture = IMG_LoadTexture(renderer, "attack.png");
    if (attackPowerUpTexture == nullptr) 
    {
        cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
        SDL_DestroyTexture(attackPowerUpTexture);
    }
    srcRect = {0,0,512,512};
    moverRect = {x,y,100,100};
}

void AttackPowerUp::render()
{
    SDL_RenderCopy(renderer, attackPowerUpTexture, &srcRect, &moverRect);
}

void AttackPowerUp::applyPowerUp(){}
