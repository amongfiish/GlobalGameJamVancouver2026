#ifndef FADE_HPP
#define FADE_HPP

#include "LeoEngine/RenderTarget.hpp"

class Fade
{
public:
    enum class FadeDirection
    {
        IN,
        OUT
    };

    void setTarget();
    void unsetTarget();

    void fade(FadeDirection fadeDirection, double fadeSeconds);

    bool update(double deltaTime);
    void draw();

private:
    LeoEngine::RenderTarget _renderTarget;

    FadeDirection _fadeDirection;
    double _fadeSeconds;

    double _elapsedSeconds;

    double _opacity;
};

#endif

