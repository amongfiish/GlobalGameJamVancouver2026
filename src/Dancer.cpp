#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Animation.hpp"
#include "Dancer.hpp"
#include "Level.hpp"

const std::shared_ptr<LeoEngine::Animation> Dancer::IDLE_ANIMATIONS[] = {
    LeoEngine::createAnimationFromStripData("bauta.png", SIZE, SIZE, NUMBER_OF_IDLE_ANIMATION_FRAMES, IDLE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("colombina.png", SIZE, SIZE, NUMBER_OF_IDLE_ANIMATION_FRAMES, IDLE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("gatto.png", SIZE, SIZE, NUMBER_OF_IDLE_ANIMATION_FRAMES, IDLE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("jester.png", SIZE, SIZE, NUMBER_OF_IDLE_ANIMATION_FRAMES, IDLE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("medico.png", SIZE, SIZE, NUMBER_OF_IDLE_ANIMATION_FRAMES, IDLE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("volto.png", SIZE, SIZE, NUMBER_OF_IDLE_ANIMATION_FRAMES, IDLE_ANIMATION_FRAME_DISPLAY_LENGTH)
};

const std::shared_ptr<LeoEngine::Animation> Dancer::VICTORY_ANIMATIONS[] = {
    LeoEngine::createAnimationFromStripData("bauta_unmask_victory.png", SIZE, SIZE, NUMBER_OF_VICTORY_ANIMATION_FRAMES, VICTORY_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("colombina_unmask_victory.png", SIZE, SIZE, NUMBER_OF_VICTORY_ANIMATION_FRAMES, VICTORY_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("gatto_unmask_victory.png", SIZE, SIZE, NUMBER_OF_VICTORY_ANIMATION_FRAMES, VICTORY_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("jester_unmask_victory.png", SIZE, SIZE, NUMBER_OF_VICTORY_ANIMATION_FRAMES, VICTORY_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("medico_unmask_victory.png", SIZE, SIZE, NUMBER_OF_VICTORY_ANIMATION_FRAMES, VICTORY_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("volto_unmask_victory.png", SIZE, SIZE, NUMBER_OF_VICTORY_ANIMATION_FRAMES, VICTORY_ANIMATION_FRAME_DISPLAY_LENGTH)
};

const std::shared_ptr<LeoEngine::Animation> Dancer::FAILURE_ANIMATIONS[] = {
    LeoEngine::createAnimationFromStripData("bauta_unmask_failure.png", SIZE, SIZE, NUMBER_OF_FAILURE_ANIMATION_FRAMES, FAILURE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("colombina_unmask_failure.png", SIZE, SIZE, NUMBER_OF_FAILURE_ANIMATION_FRAMES, FAILURE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("gatto_unmask_failure.png", SIZE, SIZE, NUMBER_OF_FAILURE_ANIMATION_FRAMES, FAILURE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("jester_unmask_failure.png", SIZE, SIZE, NUMBER_OF_FAILURE_ANIMATION_FRAMES, FAILURE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("medico_unmask_failure.png", SIZE, SIZE, NUMBER_OF_FAILURE_ANIMATION_FRAMES, FAILURE_ANIMATION_FRAME_DISPLAY_LENGTH),
    LeoEngine::createAnimationFromStripData("volto_unmask_failure.png", SIZE, SIZE, NUMBER_OF_FAILURE_ANIMATION_FRAMES, FAILURE_ANIMATION_FRAME_DISPLAY_LENGTH)
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
    _sprite.setAnimation(IDLE_ANIMATIONS[static_cast<int>(_type)]);
    _sprite.getSprite().setSize(SIZE, SIZE);
}

Dancer::~Dancer()
{

}

double adjustForBounce(double n)
{
    int floorN = static_cast<int>(floor(n));
    int modFloorN = (floorN % 4 + 4) % 4;

    bool flipN = modFloorN == 1 || modFloorN == 2;

    double fracN = n - floorN;
    
    int modTwoN = modFloorN % 2;

    double adjustedN = fracN;
    if (modTwoN != 0)
    {
        adjustedN -= 1;
    }

    if (flipN)
    {
        adjustedN *= -1;
    }

    return adjustedN;
}

void Dancer::update(double deltaTime)
{
    _elapsedTime += deltaTime * (_speed * _levelSpeedMultiplier);

    LeoEngine::Pair<double, double> rawPosition = (*_positionFunction)(_elapsedTime + _initialTime);
    
    // apply scale first
    LeoEngine::Pair<double, double> transformedPosition(rawPosition.first * _scale.first + _origin.first, rawPosition.second * _scale.second + _origin.second);

    double adjustedX = adjustForBounce(transformedPosition.first);
    double adjustedY = adjustForBounce(transformedPosition.second);

    _absolutePosition.first = adjustedX * Level::DANCE_FLOOR_WIDTH/2 + Level::DANCE_FLOOR_START_X + Level::DANCE_FLOOR_WIDTH/2 - SIZE/2;
    _absolutePosition.second = adjustedY * Level::DANCE_FLOOR_HEIGHT/2 + Level::DANCE_FLOOR_START_Y + Level::DANCE_FLOOR_HEIGHT/2 - SIZE + 6;

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

Dancer::Type Dancer::getType() const
{
    return _type;
}

void Dancer::setType(Type type)
{
    _type = type;
    _sprite.setAnimation(IDLE_ANIMATIONS[static_cast<int>(type)]);
}

