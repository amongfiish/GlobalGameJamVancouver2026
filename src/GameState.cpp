#include "LeoEngine/RandomNumberGenerator.hpp"
#include "GameState.hpp"
#include "Levels.hpp"

std::shared_ptr<Level> GameState::_currentLevel(nullptr);
double GameState::_timer = 0.0;
int GameState::_level = 0;

void GameState::setCurrentLevel(std::shared_ptr<Level> level)
{
    _currentLevel = std::move(level);
}

std::shared_ptr<Level> GameState::getCurrentLevel()
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

void GameState::resetLevel()
{
    _level = 0;
}

void GameState::nextLevel()
{
    static LeoEngine::RandomNumberGenerator _rng;

    _level++;

    _currentLevel = Levels::levelMakers[_rng.getNextNumber(0, Levels::NUMBER_OF_LEVEL_MAKERS-1)](_level);
}

int GameState::getLevel()
{
    return _level;
}

