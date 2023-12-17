#include "unit.hpp"
#include <vector>
#include "projectile.hpp"

class Goblin : public Unit
{
    public:
    Goblin(){}
    Goblin(SDL_Renderer* _renderer);
    SDL_Texture* goblinTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    const std::vector<Projectile*>& getProjectiles() const;
    void render();
    void updateProjectiles();
    void takeDamage(int);
    void renderHealthText();
    int getHealth();
    void update();
    private:
    int goblinHealth = 100;
    int goblinVelocityY = 5;
    std::vector<Projectile*> projectiles; 
    Uint32 lastProjectileTime;
    // Uint32 currentTime;

};


