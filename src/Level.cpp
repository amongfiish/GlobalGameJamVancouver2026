#include "Level.hpp"

Level::Level()
    : _targetType(Dancer::Type::DANCER_A),
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
        reSortDancerByY(_dancers, i);
    }
}

void Level::draw()
{
    for (int i = 0; i < _dancers.size(); i++)
    {
        _dancers.at(i).draw();
    }
}

void Level::setSpeedMultiplier(double speedMultiplier)
{
    _speedMultiplier = speedMultiplier;
    for (auto dancer : _dancers)
    {
        dancer.setLevelSpeedMultiplier(speedMultiplier);
    }
}

void Level::setTargetType(Dancer::Type targetType)
{
    _targetType = targetType;
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
    reSortDancerByY(_dancers, newDancerIndex);
}

