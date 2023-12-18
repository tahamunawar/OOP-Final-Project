#include "Spiderman.hpp"

Spiderman::Spiderman(SDL_Renderer* _renderer) : velocityX(0), velocityY(0), gravity(0.5), isJumping(false), attackBoostActive(false), attackBoostStartTime(0), attackBoostDuration(10000)
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

    // attack boost text stuff
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_DestroyTexture(spidermanTexture);
        // Handle initialization error as needed
    }

    // Load font
    font = TTF_OpenFont("font2.ttf", 24); // Adjust the path and size based on your requirements
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyTexture(spidermanTexture);
        TTF_Quit();
        // Handle font loading error as needed
    }

    // Set up initial values for text rendering
    textSurface = nullptr;
    textTexture = nullptr;
    textRect = { 0, 0, 0, 0 };
}

void Spiderman::render()
{
    SDL_RenderCopy(renderer, spidermanTexture, &srcRect, &moverRect);
    renderHealthText();
    renderAttackBoostMessage();
    if (!webs.empty())
    {
        for (auto& it : webs)
        {
            it->render();
        }
    }
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
        velocityY = -12; // Adjust the value based on your game
        isJumping = true;
    }
}

// Function to update Spiderman's position based on velocities
// void Spiderman::update()
// {
//     moverRect.x += static_cast<int>(velocityX);
//     moverRect.y += static_cast<int>(velocityY);

//     // Apply gravity
//     velocityY += gravity;

//     // Check if Spiderman is on the ground (you might need to adjust this based on your game)
//     if (moverRect.y >= 420)
//     {
//         moverRect.y = 420;
//         isJumping = false;
//         velocityY = 0;
//     }
// }

void Spiderman::update() {
    // Only update the position if Spiderman has not just landed
    if (!justLanded) {
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

    // Reset the justLanded flag
    justLanded = false;
    updateWeb();
}

// void Spiderman::decreaseHealth()
// {
//     spiderHealth-=10;
// }

int Spiderman::getHealth()
{
    return spiderHealth;
}

void Spiderman::increaseHealth()
{
    spiderHealth+=20;
    if (spiderHealth>100)
        spiderHealth = 100;
}

void Spiderman::activateAttackBoost()
{
    attackBoostActive = true;
    attackBoostStartTime = SDL_GetTicks();
    // Display message on the screen (you can replace this with your rendering logic)
    std::cout << "Attack boost active" << std::endl;
    damagePerAttack = 20;
}

void Spiderman::updateAttackBoost()
{
    // Check if the attack boost duration has elapsed
    if (attackBoostActive && SDL_GetTicks() - attackBoostStartTime >= attackBoostDuration)
    {
        attackBoostActive = false;
        // Clear the message on the screen (you can replace this with your rendering logic)
        std::cout << "Attack boost expired" << std::endl;
        damagePerAttack = 10;
    }
}

void Spiderman::renderAttackBoostMessage()
{
    if (attackBoostActive)
    {
        // Render the attack boost message on the screen
        std::string message = "Attack boost active";
        
        // Create text surface
        SDL_Color textColor = { 0, 255, 0 }; // White color
        textSurface = TTF_RenderText_Solid(font, message.c_str(), textColor);
        if (textSurface == nullptr) {
            std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
            // Handle text rendering error as needed
            return;
        }

        // Create text texture
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == nullptr) {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            // Handle texture creation error as needed
            SDL_FreeSurface(textSurface);
            return;
        }

        // Set text rendering position
        textRect.x = 10;
        textRect.y = 50; // Adjust the position based on your requirements
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        // Render the text texture
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        // Clean up the text surface and texture
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void Spiderman::renderHealthText()
{
    // Render Spiderman's health on the screen
    std::string healthText = "Spiderman Health: " + std::to_string(spiderHealth);
    SDL_Surface* healthSurface = TTF_RenderText_Solid(font, healthText.c_str(), {255, 255, 255});
    SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);

    SDL_Rect healthRect = {10, 10, healthSurface->w, healthSurface->h};
    SDL_RenderCopy(renderer, healthTexture, nullptr, &healthRect);

    // Clean up the health surface and texture
    SDL_FreeSurface(healthSurface);
    SDL_DestroyTexture(healthTexture);
}

// SUSSY BAKA
void Spiderman::handleCollision(const SDL_Rect& platformRect) {
    // Check if Spiderman is moving downwards (falling)
    if (velocityY > 0) {
        // Check if the bottom of Spiderman is above the top of the platform and
        // if the top of Spiderman is below the bottom of the platform
        if (moverRect.y + moverRect.h > platformRect.y &&
            moverRect.y < platformRect.y + platformRect.h) {
            // Check if Spiderman was not on the platform in the previous frame
            if (!justLanded) {
                // Adjust Spiderman's position and velocity based on the collision
                moverRect.y = platformRect.y - moverRect.h - 1; // Place Spiderman on top of the platform
                velocityY = 0; // Stop Spiderman from falling further
                isJumping = false; // Allow Spiderman to jump again

                // Set a flag to indicate that Spiderman has just landed
                justLanded = true;

                // Add any additional logic you need for landing on a platform
            }
        } else {
            // If Spiderman is not colliding with the platform, reset the justLanded flag
            justLanded = false;
        }
    }
}
// sussy end
void Spiderman::shootWeb()
{
    Projectile* temp = new Projectile(renderer, "spiderman_sprite_sheet.png", "spider", moverRect.x + 80, moverRect.y+70);
    webs.push_back(temp);   
}

void Spiderman::updateWeb()
{
    for (auto it = webs.begin(); it != webs.end(); )
    {
        (*it)->move();  // Use -> to access member functions for pointers

        // Check if the projectile should be marked for deletion
        if ((*it)->isMarkedForDeletion())
        {
            delete *it;  // Free the memory for the projectile
            it = webs.erase(it);
        }
        else
        {
            it++;
        }
    }
}

const std::vector<Projectile*>& Spiderman::getWebs() const 
{
    return webs;
}

int Spiderman::getDamage()
{
    return damagePerAttack;
}

Spiderman Spiderman::operator-(int damage) {
    // Subtract the damage from Spiderman's health
    spiderHealth -= damage;
    return *this;
}
