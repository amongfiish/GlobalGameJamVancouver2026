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
        BAUTA=0,
        COLOMBINA,
        GATTO,
        JESTER,
        MEDICO,
        VOLTO 
    };

    Dancer(std::function<LeoEngine::Pair<double, double>(double)>* positionFunction, LeoEngine::Pair<double, double> position, LeoEngine::Pair<double, double> scale, double initialTime, double speed);
    ~Dancer();

    void update(double deltaTime);
    void draw();

    void reset();

    LeoEngine::Pair<int, int> getAbsolutePosition() const;

    void setLevelSpeedMultiplier(double multiplier);

    void setType(Type type);

    static constexpr int NUMBER_OF_TYPES = 6;

    static constexpr int SIZE = 32;

private:
    static const std::shared_ptr<LeoEngine::Animation> _ANIMATIONS[NUMBER_OF_TYPES];

    static constexpr int _NUMBER_OF_ANIMATION_FRAMES = 1;
    static constexpr double _ANIMATION_FRAME_DISPLAY_LENGTH = 0.1;


    Type _type;

    double _elapsedTime;

    std::function<LeoEngine::Pair<double, double>(double)>* _positionFunction;

    // transform for character dance pattern
    LeoEngine::Pair<double, double> _origin;
    LeoEngine::Pair<double, double> _scale;

    // time to offset function time parameter by
    double _initialTime;
    double _speed;

    double _levelSpeedMultiplier;

    // position at which the character is drawn
    LeoEngine::Pair<int, int> _absolutePosition;

    LeoEngine::SpriteAnimated _sprite;
};

void reSortDancerByY(std::vector<Dancer>& dancerVector, int i);

#endif

