#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include "LeoEngine/SpriteStatic.hpp"
#include "LeoEngine/UIText.hpp"
#include "Dancer.hpp"

class Level
{
public:
    Level();
    ~Level();

    void update(double deltaTime);
    void draw();

    void reset();

    void setSpeedMultiplier(double speedMultiplier);
    void setTargetType(Dancer::Type targetType);

    void randomizeDancerTypes(std::vector<Dancer::Type> types);
    void setTarget(int i);

    std::vector<Dancer>& getDancers();

    void addDancer(Dancer&& dancer);

    static constexpr int BACKGROUND_START_X = 128;
    static constexpr int BACKGROUND_START_Y = 0;
    static constexpr int BACKGROUND_WIDTH = 256;
    static constexpr int BACKGROUND_HEIGHT = 256;

    static constexpr int DANCE_FLOOR_START_X = 128;
    static constexpr int DANCE_FLOOR_START_Y = 48;
    static constexpr int DANCE_FLOOR_WIDTH = 256;
    static constexpr int DANCE_FLOOR_HEIGHT = 208;

    static constexpr double SUCCESS_DELTA_TIME = 5.0;
    static constexpr double FAILURE_DELTA_TIME = -10.0;

private:
    static LeoEngine::SpriteStatic _backgroundSprite;
    static LeoEngine::SpriteStatic _makeBackgroundSprite();

    LeoEngine::UIText _timerTextBox;
    void _initializeTimerTextBox();

    std::vector<Dancer> _dancers;
    int _target;
    Dancer::Type _targetType;

    double _speedMultiplier;
};

#endif

