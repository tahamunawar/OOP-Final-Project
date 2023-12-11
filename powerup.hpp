#include "unit.hpp"
#pragma once

class PowerUp : public Unit
{
    public:
    virtual void applyPowerUp() = 0;
};