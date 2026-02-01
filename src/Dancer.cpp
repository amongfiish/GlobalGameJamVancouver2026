#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Animation.hpp"
#include "Dancer.hpp"
#include "Level.hpp"

const std::shared_ptr<LeoEngine::Animation> Dancer::_ANIMATIONS[] = {
    LeoEngine::createAnimationFromStripData("bauta.png", SIZE, SIZE, _NUMBER_OF_ANIMATION_FRAMES, _ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("colombina.png", SIZE, SIZE, _NUMBER_OF_ANIMATION_FRAMES, _ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("gatto.png", SIZE, SIZE, _NUMBER_OF_ANIMATION_FRAMES, _ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("jester.png", SIZE, SIZE, _NUMBER_OF_ANIMATION_FRAMES, _ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("medico.png", SIZE, SIZE, _NUMBER_OF_ANIMATION_FRAMES, _ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("volto.png", SIZE, SIZE, _NUMBER_OF_ANIMATION_FRAMES, _ANIMATION_FRAME_DISPLAY_LENGTH)
};

Dancer::Dancer(std::function<LeoEngine::Pair<double, double>(double)>* positionFunction, LeoEngine::Pair<double, double> origin, LeoEngine::Pair<double, double> scale, double initialTime, double speed)
    : _type(static_cast<Type>(0)),
      _elapsedTime(0.0),
      _positionFunction(positionFunction),
      _origin(origin), _scale(scale),
      _initialTime(initialTime),
      _speed(speed),
      _levelSpeedMultiplier(1.0)
{
    _sprite.setAnimation(_ANIMATIONS[static_cast<int>(_type)]);
    _sprite.getSprite().setSize(SIZE, SIZE);
}

Dancer::~Dancer()
{

}

void Dancer::update(double deltaTime)
{
    _elapsedTime += deltaTime * (_speed * _levelSpeedMultiplier);

    LeoEngine::Pair<double, double> rawPosition = (*_positionFunction)(_elapsedTime + _initialTime);
    
    // apply scale first
    LeoEngine::Pair<double, double> transformedPosition(rawPosition.first * _scale.first + _origin.first, rawPosition.second * _scale.second + _origin.second);

    // wrap position
    while (transformedPosition.first < -1.0)
    {
        transformedPosition.first += 2.0;
    }
    while (transformedPosition.first > 1.0)
    {
        transformedPosition.first -= 2.0;
    }
    while (transformedPosition.second < -1.0)
    {
        transformedPosition.second += 2.0;
    }
    while (transformedPosition.second > 1.0)
    {
        transformedPosition.second -= 2.0;
    }

    _absolutePosition.first = transformedPosition.first * Level::DANCE_FLOOR_WIDTH/2 + Level::DANCE_FLOOR_START_X + Level::DANCE_FLOOR_WIDTH/2 - SIZE/2;
    _absolutePosition.second = transformedPosition.second * Level::DANCE_FLOOR_HEIGHT/2 + Level::DANCE_FLOOR_START_Y + Level::DANCE_FLOOR_HEIGHT/2 - SIZE + 6;

    _sprite.getSprite().setPosition(_absolutePosition.first, _absolutePosition.second);

    _sprite.update(deltaTime);
}

void Dancer::draw()
{
    _sprite.draw();
}

void Dancer::reset()
{
    _elapsedTime = 0.0;
    setType(static_cast<Type>(0));
    update(0.0);
}

LeoEngine::Pair<int, int> Dancer::getAbsolutePosition() const
{
    return _absolutePosition;
}

void Dancer::setLevelSpeedMultiplier(double multiplier)
{
    _levelSpeedMultiplier = multiplier;
}

void Dancer::setType(Type type)
{
    _type = type;
    _sprite.setAnimation(_ANIMATIONS[static_cast<int>(type)]);
}

void reSortDancerByY(std::vector<Dancer>& dancerVector, int i)
{
    int j = i;
    bool sorted = false;
    while (j != 0 && dancerVector.at(j-1).getAbsolutePosition().second > dancerVector.at(j).getAbsolutePosition().second)
    {
        Dancer tempDancer = std::move(dancerVector.at(j));
        dancerVector.at(j) = dancerVector.at(j-1);
        dancerVector.at(j-1) = tempDancer;
        j--;
    }
}

