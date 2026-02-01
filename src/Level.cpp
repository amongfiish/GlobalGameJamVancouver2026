#include <string>
#include <cmath>
#include "LeoEngine/RandomNumberGenerator.hpp"
#include "Level.hpp"
#include "GameState.hpp"

LeoEngine::SpriteStatic Level::_backgroundSprite = _makeBackgroundSprite();

Level::Level()
    : _targetType(static_cast<Dancer::Type>(0)),
      _speedMultiplier(1.0)
{

}

Level::~Level()
{

}

void Level::update(double deltaTime)
{
    for (int i = 0; i < _dancers.size(); i++)
    {
        _dancers.at(i).update(deltaTime);
        _reSortDancerByY(i);
    }
}

void Level::draw()
{
    _backgroundSprite.draw();

    for (int i = 0; i < _dancers.size(); i++)
    {
        _dancers.at(i).draw();
    }
}

void Level::reset()
{
    GameState::resetTime();

    for (auto& dancer : _dancers)
    {
        dancer.reset();
    }
}

void Level::setSpeedMultiplier(double speedMultiplier)
{
    _speedMultiplier = speedMultiplier;
    for (auto& dancer : _dancers)
    {
        dancer.setLevelSpeedMultiplier(_speedMultiplier);
    }
}

void Level::setTargetType(Dancer::Type targetType)
{
    _targetType = targetType;
    _target->setType(targetType);
}

Dancer* Level::getTarget()
{
    return _target;
}

void Level::randomizeDancerTypes(std::vector<Dancer::Type> types)
{
    static LeoEngine::RandomNumberGenerator rng(18473);

    for (auto& dancer : _dancers)
    {
        dancer.setType(types.at(rng.getNextNumber(0, types.size()-1)));
    }
}

void Level::setTarget(int i)
{
    _target = &_dancers.at(i);
    _target->setType(_targetType);
}

LeoEngine::Rectangle<int> Level::getTargetBounds() const
{
    LeoEngine::Rectangle<int> bounds;
    
    LeoEngine::Pair<int, int> targetPosition = _target->getAbsolutePosition();
    bounds.x = targetPosition.first;
    bounds.y = targetPosition.second;
    bounds.width = Dancer::SIZE;
    bounds.height = Dancer::SIZE;

    return bounds;
}

std::vector<Dancer>& Level::getDancers()
{
    return _dancers;
}

void Level::addDancer(Dancer&& dancer)
{
    _dancers.emplace_back(dancer);

    int newDancerIndex = _dancers.size() - 1;
    _dancers.at(newDancerIndex).setLevelSpeedMultiplier(_speedMultiplier);

    _reSortDancerByY(newDancerIndex);
}

LeoEngine::SpriteStatic Level::_makeBackgroundSprite()
{
    LeoEngine::SpriteStatic sprite("background.png");
    sprite.setPosition(BACKGROUND_START_X, BACKGROUND_START_Y);
    sprite.setSize(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    return sprite;
}

void Level::_reSortDancerByY(int i)
{
    while (i != 0 && _dancers.at(i-1).getAbsolutePosition().second > _dancers.at(i).getAbsolutePosition().second)
    {
        Dancer tempDancer = std::move(_dancers.at(i));

        _dancers.at(i) = _dancers.at(i-1);
        _dancers.at(i-1) = tempDancer;

        if (&_dancers.at(i) == _target)
        {
            _target = &_dancers.at(i-1);
        }
        else if (&_dancers.at(i-1) == _target)
        {
            _target = &_dancers.at(i);
        }

        i--;
    }
}

