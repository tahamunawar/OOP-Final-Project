#include "goblin.hpp"

Goblin::Goblin(SDL_Renderer* _renderer)
{
    renderer = _renderer;
    goblinTexture = IMG_LoadTexture(renderer, "villain_sprite1.png");
    if (goblinTexture == nullptr) 
    {
        cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
        SDL_DestroyTexture(goblinTexture);
    }
    srcRect = {191,15,76,61};
    moverRect = {850,450,150,150};
}

void Goblin::render()
{
    SDL_RenderCopy(renderer, goblinTexture, &srcRect, &moverRect);
}

