#include "powerup.hpp"

class AttackPowerUp : public PowerUp
{
    public:
    AttackPowerUp(SDL_Renderer* _renderer, int, int);
    void applyPowerUp(Spiderman&) override;
    SDL_Texture* attackPowerUpTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    void render() override;
};