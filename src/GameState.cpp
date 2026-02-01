#include "GameState.hpp"

std::unique_ptr<Level> GameState::_currentLevel(nullptr);
double GameState::_timer = 0.0;

void GameState::setCurrentLevel(std::unique_ptr<Level> level)
{
    _currentLevel = std::move(level);
}

Level* GameState::getCurrentLevel()
{
    return _currentLevel.get();
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

