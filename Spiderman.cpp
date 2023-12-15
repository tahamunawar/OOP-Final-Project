#include "Spiderman.hpp"

Spiderman::Spiderman(SDL_Renderer* _renderer) : velocityX(0), velocityY(0), gravity(0.5), isJumping(false)
{
    renderer = _renderer;
    spidermanTexture = IMG_LoadTexture(renderer, "spiderman_sprite_sheet.png");
    if (spidermanTexture == nullptr) 
    {
        cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
        SDL_DestroyTexture(spidermanTexture);
    }
    srcRect = {23, 79, 23, 44};
    moverRect = {50, 420, 80, 130};
}

void Spiderman::render()
{
    SDL_RenderCopy(renderer, spidermanTexture, &srcRect, &moverRect);
}

void Spiderman::moveLeft()
{
    velocityX = -5; // Adjust the value based on your game
}

void Spiderman::moveRight()
{
    velocityX = 5; // Adjust the value based on your game
}

void Spiderman::resetVelocity()
{
    velocityX = 0;
}
void Spiderman::jump()
{
    if (!isJumping)
    {
        velocityY = -9.8; // Adjust the value based on your game
        isJumping = true;
    }
}

// Function to update Spiderman's position based on velocities
void Spiderman::update()
{
    moverRect.x += static_cast<int>(velocityX);
    moverRect.y += static_cast<int>(velocityY);

    // Apply gravity
    velocityY += gravity;

    // Check if Spiderman is on the ground (you might need to adjust this based on your game)
    if (moverRect.y >= 420)
    {
        moverRect.y = 420;
        isJumping = false;
        velocityY = 0;
    }
}

SDL_Rect Spiderman::getMoverRect() const
{
    return moverRect;
}

void Spiderman::decreaseHealth()
{
    spiderHealth-=10;
}