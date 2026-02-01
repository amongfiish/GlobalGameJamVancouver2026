#include <cmath>
#include "Levels.hpp"
#include "DancePatterns.hpp"
#include "Dancer.hpp"

Level Levels::test = Levels::_makeTest();
Level Levels::linear = Levels::_makeLinear();
Level Levels::circle = Levels::_makeCircle();

Level Levels::_makeTest()
{
    Level level;
    level.addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    level.addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(-1.0, -1.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    level.addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(1.0, -1.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    level.addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(-1.0, 1.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    level.addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(1.0, 1.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    return level;
}

Level Levels::_makeLinear()
{
    static constexpr int NUMBER_OF_DANCERS = 10;

    Level level;
    for (int i = 0; i < NUMBER_OF_DANCERS; i++)
    {
        level.addDancer(Dancer(&DancePatterns::linear, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(1.0, 1.0), (static_cast<double>(i)/NUMBER_OF_DANCERS) * 2 - 1, 1.0));
    }

    return level;
}

Level Levels::_makeCircle()
{
    static constexpr int NUMBER_OF_DANCERS = 30;

    Level level;
    for (int i = 0; i < NUMBER_OF_DANCERS; i++)
    {
        level.addDancer(Dancer(&DancePatterns::circle, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(0.7, 0.7), (static_cast<double>(i)/NUMBER_OF_DANCERS)*M_PI*2, 1.0));
    }

    return level;
}

