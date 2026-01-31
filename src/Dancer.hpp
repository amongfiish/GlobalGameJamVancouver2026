#ifndef DANCER_HPP
#define DANCER_HPP

#include <string>
#include <functional>
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/SpriteAnimated.hpp"

class Dancer
{
public:
    // just indicates which animation to use
    enum class Type
    {
        DANCER_A=0,
        DANCER_B,
        DANCER_C,
        DANCER_D 
    };

    Dancer(Type type, std::function<LeoEngine::Pair<double, double>(double)> positionFunction, LeoEngine::Pair<double, double> position, LeoEngine::Pair<double, double> scale, double initialTime, double speed);
    ~Dancer();

    void update(double deltaTime);
    void draw();

    LeoEngine::Pair<int, int> getAbsolutePosition() const;

    static constexpr int NUMBER_OF_TYPES = 4;

    static constexpr int SIZE = 32;

private:
    static const std::string _ANIMATION_FILENAMES[NUMBER_OF_TYPES];

    static constexpr int _DANCE_FLOOR_START_X = 0;
    static constexpr int _DANCE_FLOOR_START_Y = 0;
    static constexpr int _DANCE_FLOOR_WIDTH = 256;
    static constexpr int _DANCE_FLOOR_HEIGHT = 256;

    Type _type;

    double _elapsedTime;

    std::function<LeoEngine::Pair<double, double>(double)> _positionFunction;

    // transform for character dance pattern
    LeoEngine::Pair<double, double> _origin;
    LeoEngine::Pair<double, double> _scale;

    // time to offset function time parameter by
    double _initialTime;
    double _speed;

    // position at which the character is drawn
    LeoEngine::Pair<int, int> _absolutePosition;

    LeoEngine::SpriteAnimated _sprite;
};

void reSortDancerByY(std::vector<Dancer>& dancerVector, int i);

#endif

