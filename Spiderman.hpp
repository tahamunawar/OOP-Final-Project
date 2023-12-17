#include "unit.hpp"
#include "projectile.hpp"
#include "vector"
#pragma once
// class Spiderman : public Unit
// {
//     public:
//     Spiderman(SDL_Rect, SDL_Rect);
// };

// Unit running1 = {{111,399, 37, 36}, {30, 40, 37, 36}};
// Unit running2 = {{158,400, 39, 35}, {30, 40, 39, 35}};
// Unit running3 = {{208,400, 38, 35}, {30, 40, 38, 35}};
// Unit running4 = {{260,402, 40, 34}, {30, 40, 40, 34}};
// Unit running5 = {{15,400, 38, 35}, {30, 40, 38, 35}};
// Unit running6 = {{61, 399, 40, 36}, {30, 40, 40, 36}}; 
// Unit running[] = {running1, running2, running3, running4, running5, running6};

// spiderman srcRect and moverRect for different frames have been added here

class Spiderman : public Unit
{
private:
    float velocityX;
    float velocityY;

    // Gravity value
    float gravity;

    // Jumping flag
    bool isJumping;

    int spiderHealth=100;
    int damagePerAttack=10;

    bool attackBoostActive;
    Uint32 attackBoostStartTime;
    Uint32 attackBoostDuration;
    bool justLanded = true;
public:
    Spiderman(){}
    Spiderman(SDL_Renderer* _renderer);
    SDL_Texture* spidermanTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    void render();

    void update();

    void resetVelocity();
    
    // Function to move Spiderman left
    void moveLeft();

    // Function to move Spiderman right
    void moveRight();

    void jump();

    void decreaseHealth();

    int getHealth();

    void increaseHealth();

    void activateAttackBoost();
    void updateAttackBoost();

    // Function to render the attack boost message
    void renderAttackBoostMessage();

    // Function render the health text message
    void renderHealthText();

    // variables for rendering the attack boost message
    TTF_Font* font;
    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Rect textRect;

    std::vector<Projectile*> webs;

    void shootWeb();
    void updateWeb();
    const std::vector<Projectile*>& getWebs() const;

    int getDamage();
    // SUSSY BAKA
    void handleCollision(const SDL_Rect&);
};