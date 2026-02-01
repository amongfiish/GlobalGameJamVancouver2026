#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <memory>
#include "Level.hpp"

class GameState
{
public:
    GameState() = delete;

    static void setCurrentLevel(std::shared_ptr<Level> level);
    static std::shared_ptr<Level> getCurrentLevel();

    static void resetTime();
    static void addTime(double deltaTime);
    static double getTime();

    static void resetLevel();
    static void nextLevel();
    static int getLevel();

private:
    static constexpr double _INITIAL_TIMER = 14.0;

    static std::shared_ptr<Level> _currentLevel;

    // how long does the player have left?
    static double _timer;

    // how many levels have been cleared?
    static int _level;
};

#endif

