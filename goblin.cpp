#include "goblin.hpp"

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
    // currentTime = SDL_GetTicks();
}

void Goblin::render()
{
    SDL_RenderCopy(renderer, goblinTexture, &srcRect, &moverRect);

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

    // Add a new projectile every few seconds (e.g., every 2000 milliseconds)
    if (currentTime - lastProjectileTime >= 2000)
    {
        Projectile* temp = new Projectile(renderer, "villain_sprite1.png", "goblin");
        projectiles.push_back(temp);
        lastProjectileTime = currentTime;
    }

    // Update and move existing projectiles
    for (auto it = projectiles.begin(); it != projectiles.end(); )
    {
        (*it)->move();  // Use -> to access member functions for pointers

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

