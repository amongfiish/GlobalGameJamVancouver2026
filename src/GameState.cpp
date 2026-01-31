#include "GameState.hpp"

Level* GameState::_currentLevel = nullptr;

void GameState::setCurrentLevel(Level& level)
{
    _currentLevel = &level;
}

Level& GameState::getCurrentLevel()
{
    return *_currentLevel;
}

