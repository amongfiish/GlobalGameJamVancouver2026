#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "Character.hpp"

Character::Character(LeoEngine::Pair<double, double> initialPosition, LeoEngine::Colour colour)
    : _position(initialPosition),
      _colour(colour)
{

}

void Character::draw()
{
    LeoEngine::Services::get().getGraphics()->drawRectangle(_colour, false, LeoEngine::Rectangle<int>(_position.first, _position.second, _SIZE, _SIZE));
}

