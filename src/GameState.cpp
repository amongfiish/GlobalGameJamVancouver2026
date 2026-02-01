#include "GameState.hpp"

Level* GameState::_currentLevel = nullptr;
double GameState::_timer = 0.0;

void GameState::setCurrentLevel(Level* level)
{
    _currentLevel = level;
}

Level* GameState::getCurrentLevel()
{
    return _currentLevel;
}

void GameState::resetTime()
{
    _timer = _INITIAL_TIMER;
}

void GameState::addTime(double deltaTime)
{
    _timer += deltaTime;
}

double GameState::getTime()
{
    return _timer;
}

