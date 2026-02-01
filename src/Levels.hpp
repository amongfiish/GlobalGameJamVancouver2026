#ifndef LEVELS_HPP
#define LEVELS_HPP

#include <memory>
#include <functional>
#include "LeoEngine/RandomNumberGenerator.hpp"
#include "Level.hpp"

class Levels
{
public:
    Levels() = delete;
    
    static constexpr int NUMBER_OF_LEVEL_MAKERS = 3;
    static std::function<std::unique_ptr<Level>(int)> levelMakers[NUMBER_OF_LEVEL_MAKERS];

    static std::unique_ptr<Level> makeTest();
    static std::unique_ptr<Level> makeTutorial();
    static std::unique_ptr<Level> makeLine();

    static std::unique_ptr<Level> makeStatic(int difficulty);
    static std::unique_ptr<Level> makeColinear(int difficulty);
    static std::unique_ptr<Level> makeLinearScatter(int difficulty);
    //static Level* makeCircle();
    //static Level makeStatic(int difficulty);

private:
    static Dancer::Type _getRandomType();
    static LeoEngine::RandomNumberGenerator _rng;
};

#endif

