#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Level.hpp"

class GameState
{
public:
    GameState() = delete;

    static void setCurrentLevel(Level& level);
    static Level& getCurrentLevel();

private:
    static Level* _currentLevel;
};

#endif

