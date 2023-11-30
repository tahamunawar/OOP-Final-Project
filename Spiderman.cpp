#include "Spiderman.hpp"

Spiderman::Spiderman(SDL_Renderer* _renderer)
{
    renderer = _renderer;
    spidermanTexture = IMG_LoadTexture(renderer, "spiderman_sprite_sheet.png");
    if (spidermanTexture == nullptr) 
    {
        cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
        SDL_DestroyTexture(spidermanTexture);
    }
    srcRect = {23, 79, 23, 44};
    moverRect = {50, 450, 100, 200};
}

void Spiderman::render()
{
    SDL_RenderCopy(renderer, spidermanTexture, &srcRect, &moverRect);
}