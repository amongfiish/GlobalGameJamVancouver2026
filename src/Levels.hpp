#ifndef LEVELS_HPP
#define LEVELS_HPP

#include <memory>
#include "LeoEngine/RandomNumberGenerator.hpp"
#include "Level.hpp"

class Levels
{
public:
    Levels() = delete;

    static std::unique_ptr<Level> makeTest();
    static std::unique_ptr<Level> makeTutorial();
    static std::unique_ptr<Level> makeLine();
    static std::unique_ptr<Level> makeStatic(int gridSize, int numberOfDancers);
    static std::unique_ptr<Level> makeColinear(int numberOfDancers);
    //static Level* makeCircle();
    //static Level makeStatic(int difficulty);

private:
    static Dancer::Type _getRandomType();
    static LeoEngine::RandomNumberGenerator _rng;
};

#endif

