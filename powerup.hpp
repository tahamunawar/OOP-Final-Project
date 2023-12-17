#include "unit.hpp"
#include "Spiderman.hpp"
#pragma once

class PowerUp : public Unit
{
    private:
    bool MarkedForDeletion=0;
    public:
    virtual void applyPowerUp(Spiderman&) = 0;
    bool isMarkedForDeletion();
    void MarkForDeletion();
    virtual void render(){};
    virtual ~PowerUp(){};
    
};