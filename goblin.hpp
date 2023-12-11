#include "unit.hpp"

class Goblin : public Unit
{
    public:
    Goblin(SDL_Renderer* _renderer);
    SDL_Texture* goblinTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    void render();
};


