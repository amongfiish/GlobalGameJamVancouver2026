#ifndef CHARACTER_FIXED_MOVEMENT_HPP
#define CHARACTER_FIXED_MOVEMENT_HPP

#include "Character.hpp"

class CharacterFixedMovement : public Character
{
public:
    CharacterFixedMovement(LeoEngine::Pair<double, double> initialPosition, LeoEngine::Colour colour, LeoEngine::Pair<double, double> initialVelocity);

    virtual void update(double deltaTime) override;

private:
    LeoEngine::Pair<double, double> _velocity;
};

#endif

