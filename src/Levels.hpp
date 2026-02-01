#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "Level.hpp"

class Levels
{
public:
    Levels() = delete;

    static Level test;
    static Level linear;
    static Level circle;

private:
    static Level _makeTest();
    static Level _makeLinear();
    static Level _makeCircle();
};

#endif

