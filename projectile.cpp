#include "projectile.hpp"

Projectile::Projectile(SDL_Renderer* _renderer, const char * _imgPath, const char * owner, int x, int y)
{
    imgPath = _imgPath;
    renderer = _renderer;
    projectileTexture = IMG_LoadTexture(renderer, imgPath);
    if (projectileTexture == nullptr) 
    {
        cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
    }
    if (std::strcmp(imgPath, "villain_sprite1.png") == 0)
    {
        srcRect = {107,32,12,13};
        moverRect = {x,y,50,50};
    }
    else
    {
        srcRect = {59,349,11,4};
        moverRect = {x,y,20,20};
    }
    movingSpeed = 10;
    markedForDeletion = false;
}

void Projectile::render()
{
    if (projectileTexture != nullptr)
    {
        SDL_RenderCopy(renderer, projectileTexture, &srcRect, &moverRect);
    }
}

void Projectile::move()
{
    // Move the projectile to the left if it is of any villain
    if (std::strcmp(imgPath, "villain_sprite1.png") == 0)
        moverRect.x -= movingSpeed; 
    // otherwise move projectile to the right if it is of spiderman    
    else
        moverRect.x += movingSpeed;
    
    if (moverRect.x < 0 or moverRect.x > 1000)
        markedForDeletion = true;
}

bool Projectile::isMarkedForDeletion()
{
    return markedForDeletion;
}

// void Projectile::setMovingSpeed(int value)
// {
//     movingSpeed = value;
// }

// void Projectile::setDamageDealt(int value)
// {
//     damageDealt = value;
// }

Projectile::~Projectile()
{
    SDL_DestroyTexture(projectileTexture);
}

void Projectile::markForDeletion() 
{
    markedForDeletion = true;
}

