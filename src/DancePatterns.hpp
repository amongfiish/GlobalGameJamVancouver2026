#ifndef DANCE_PATTERNS_HPP
#define DANCE_PATTERNS_HPP

#include <functional>
#include "LeoEngine/Pair.hpp"

class DancePatterns
{
public:
    typedef std::function<LeoEngine::Pair<double, double>(double)> DancePattern;

    DancePatterns() = delete;

    static DancePattern still;
    static DancePattern linear;
    static DancePattern circle; 
    static DancePattern flower;
};

#endif

