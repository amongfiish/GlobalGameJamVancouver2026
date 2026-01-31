#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "Dancer.hpp"

class Level
{
public:
    Level(std::vector<Dancer> dancers, Dancer::Type targetType);
    ~Level();

private:
    std::vector<Dancer> _dancers;
};

#endif

