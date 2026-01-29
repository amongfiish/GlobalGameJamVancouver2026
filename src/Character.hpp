#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Colour.hpp"

class Character
{
public:
    Character(LeoEngine::Pair<double, double> initialPosition, LeoEngine::Colour colour);

    virtual void update(double deltaTime) = 0;
    void draw();

protected:
    static constexpr int _SIZE = 10;

    static constexpr int _MIN_X = 0;
    static constexpr int _MAX_X = 200;
    static constexpr int _MIN_Y = 0;
    static constexpr int _MAX_Y = 200;

    LeoEngine::Pair<double, double> _position;
    LeoEngine::Colour _colour;
};

#endif

