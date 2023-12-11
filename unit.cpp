#include "unit.hpp"

bool Unit::operator==(const Unit& u1) const {
    return (srcRect.x == u1.srcRect.x && srcRect.y == u1.srcRect.y &&
            srcRect.w == u1.srcRect.w && srcRect.h == u1.srcRect.h);
}
