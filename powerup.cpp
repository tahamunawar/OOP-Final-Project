#include "powerup.hpp"

bool PowerUp::isMarkedForDeletion()
{
    return MarkedForDeletion;
}

void PowerUp::MarkForDeletion()
{
    MarkedForDeletion = 1;
}
