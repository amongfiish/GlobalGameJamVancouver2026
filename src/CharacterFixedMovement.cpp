#include "CharacterFixedMovement.hpp"

CharacterFixedMovement::CharacterFixedMovement(LeoEngine::Pair<double, double> initialPosition, LeoEngine::Colour colour, LeoEngine::Pair<double, double> initialVelocity)
    : Character(initialPosition, colour),
      _velocity(initialVelocity)
{

}

void CharacterFixedMovement::update(double deltaTime)
{
    _position.first += _velocity.first * deltaTime;
    _position.second += _velocity.second * deltaTime;

    if (_position.first > _MAX_X)
    {
        _position.first = _MIN_X - _SIZE;
    }
    else if (_position.first < _MIN_X - _SIZE)
    {
        _position.first = _MAX_X;
    }

    if (_position.second > _MAX_Y - _SIZE)
    {
        _position.second -= _position.second - _MAX_Y + _SIZE;
        _velocity.second *= -1;
    }
    else if (_position.second < _MIN_Y)
    {
        _position.second += _MIN_Y - _position.second;
        _velocity.second *= -1;
    }
}

