#include "powerup.hpp"

class HealthPowerUp : public PowerUp
{
    public:
    HealthPowerUp(SDL_Renderer* _renderer, int, int);
    void applyPowerUp() override;
    SDL_Texture* healthPowerUpTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    void render();
};