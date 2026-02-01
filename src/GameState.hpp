#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Level.hpp"

class GameState
{
public:
    GameState() = delete;

    static void setCurrentLevel(std::unique_ptr<Level> level);
    static Level* getCurrentLevel();

    static void resetTime();
    static void addTime(double deltaTime);
    static double getTime();

    static void nextLevel();
    static int getLevel();

private:
    static constexpr double _INITIAL_TIMER = 14.0;

    static std::unique_ptr<Level> _currentLevel;

    // how long does the player have left?
    static double _timer;

    // how many levels have been cleared?
    static int _level;
};

#endif

