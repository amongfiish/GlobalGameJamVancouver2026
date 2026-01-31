#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "Dancer.hpp"

class Level
{
public:
    Level();
    ~Level();

    void update(double deltaTime);
    void draw();

    void setSpeedMultiplier(double speedMultiplier);
    void setTargetType(Dancer::Type targetType);

    std::vector<Dancer>& getDancers();

    void addDancer(Dancer&& dancer);

private:
    std::vector<Dancer> _dancers;
    Dancer::Type _targetType;

    double _speedMultiplier;
};

#endif

