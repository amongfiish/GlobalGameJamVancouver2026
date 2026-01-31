#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Animation.hpp"
#include "Dancer.hpp"

const std::string Dancer::_ANIMATION_FILENAMES[] = {
    "test_animation.png",
    "dancer_b.png",
    "dancer_c.png",
    "dancer_d.png"
};

Dancer::Dancer(Type type, std::function<LeoEngine::Pair<double, double>(double)> positionFunction, LeoEngine::Pair<double, double> origin, LeoEngine::Pair<double, double> scale, double initialTime, double speed)
    : _type(type),
      _elapsedTime(0.0),
      _positionFunction(positionFunction),
      _origin(origin), _scale(scale),
      _initialTime(initialTime),
      _speed(speed)
{
    _sprite.setAnimation(LeoEngine::createAnimationFromStripData(_ANIMATION_FILENAMES[static_cast<int>(_type)], SIZE, SIZE, 1, 0.5));
    _sprite.getSprite().setSize(SIZE, SIZE);
}

Dancer::~Dancer()
{

}

void Dancer::update(double deltaTime)
{
    _elapsedTime += deltaTime * _speed;

    LeoEngine::Pair<double, double> rawPosition = _positionFunction(_elapsedTime + _initialTime);
    
    // apply scale first
    LeoEngine::Pair<double, double> transformedPosition(rawPosition.first * _scale.first + _origin.first, rawPosition.second * _scale.second + _origin.second);

    _absolutePosition.first = transformedPosition.first * _DANCE_FLOOR_WIDTH/2 + _DANCE_FLOOR_START_X + _DANCE_FLOOR_WIDTH/2 - SIZE/2;
    _absolutePosition.second = transformedPosition.second * _DANCE_FLOOR_HEIGHT/2 + _DANCE_FLOOR_START_Y + _DANCE_FLOOR_HEIGHT/2 - SIZE/2;

    _sprite.getSprite().setPosition(_absolutePosition.first, _absolutePosition.second);

    _sprite.update(_elapsedTime);
}

void Dancer::draw()
{
    _sprite.draw();
}

LeoEngine::Pair<int, int> Dancer::getAbsolutePosition() const
{
    return _absolutePosition;
}

void reSortDancerByY(std::vector<Dancer>& dancerVector, int i)
{
    int j = i;
    bool sorted = false;
    while (!sorted)
    {
        if (j != 0 && dancerVector.at(j-1).getAbsolutePosition().second > dancerVector.at(j).getAbsolutePosition().second)
        {
            Dancer tempDancer = std::move(dancerVector.at(j));
            dancerVector.at(j) = dancerVector.at(j-1);
            dancerVector.at(j-1) = tempDancer;
            j--;
        }
        else
        {
            break;
        }
    }
}

