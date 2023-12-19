#include "powerup.hpp"

void PowerUp::move()
{
    // Move the projectile to the left if it is of any villain
    moverRect.y += movingSpeed;

}

bool PowerUp::isMarkedForDeletion()
{
    return MarkedForDeletion;
}

void PowerUp::MarkForDeletion()
{
    MarkedForDeletion = 1;
}

