#include "goblin.hpp"

//constructor call
Goblin::Goblin(SDL_Renderer* _renderer)
{
    renderer = _renderer;
    goblinTexture = IMG_LoadTexture(renderer, "villain_sprite1.png");
    if (goblinTexture == nullptr) 
    {
        cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl;
    }
    srcRect = {191,15,76,61};
    moverRect = {840,400,150,150};
    lastProjectileTime = SDL_GetTicks();
}

//rendering goblin
void Goblin::render()
{
    SDL_RenderCopy(renderer, goblinTexture, &srcRect, &moverRect);

    renderHealthText();
    if (!projectiles.empty())
    {
        for (auto& projectile : projectiles)
        {
            projectile->render();
        }
    }
}

void Goblin::updateProjectiles()
{
    Uint32 currentTime = SDL_GetTicks();

    // Add a new projectile every few seconds
    if (currentTime - lastProjectileTime >= projectileTime)
    {
        Projectile* temp = new Projectile(renderer, "villain_sprite1.png", "goblin", moverRect.x - 10, moverRect.y + moverRect.w/2);
        projectiles.push_back(temp);
        lastProjectileTime = currentTime;
    }

    // Update and move existing projectiles
    for (auto it = projectiles.begin(); it != projectiles.end(); )
    {
        (*it)->move();

        // Check if the projectile should be marked for deletion
        if ((*it)->isMarkedForDeletion())
        {
            delete *it;  // Free the memory for the projectile
            it = projectiles.erase(it);
        }
        else
        {
            it++;
        }
    }
}

const std::vector<Projectile*>& Goblin::getProjectiles() const 
{
    return projectiles;
}

//if goblin gets shot by a web
void Goblin::takeDamage(int x)
{
    goblinHealth-=x;
}

//showing goblin's health
void Goblin::renderHealthText()
{
    TTF_Font* font = TTF_OpenFont("font2.ttf", 24);
    std::string healthText = "Goblin Health: " + std::to_string(goblinHealth);
    SDL_Surface* healthSurface = TTF_RenderText_Solid(font, healthText.c_str(), {255, 255, 255});
    SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);

    SDL_Rect healthRect = {400, 10, healthSurface->w, healthSurface->h};
    SDL_RenderCopy(renderer, healthTexture, nullptr, &healthRect);

    // Clean up the health surface and texture
    SDL_FreeSurface(healthSurface);
    SDL_DestroyTexture(healthTexture);
}

//getter for goblin's health
int Goblin::getHealth()
{
    return goblinHealth;
}

void Goblin::update()
{   
    moverRect.y += goblinVelocityY;

    if (goblinHealth <= 50 && goblinVelocityY == 5) goblinVelocityY = 8;
    if (goblinHealth <= 20 && projectileTime == 1000) projectileTime = 600;
    // Check if the goblin has reached the top or bottom of the screen
    if (moverRect.y <= 0) {
        moverRect.y = 0;
        goblinVelocityY = -goblinVelocityY; // Reverse the vertical velocity
    } else if (moverRect.y + moverRect.h >= 550) {
        moverRect.y = 550 - moverRect.h;
        goblinVelocityY = -goblinVelocityY; // Reverse the vertical velocity
    }
}