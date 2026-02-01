#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "Fade.hpp"

void Fade::setTarget()
{
    LeoEngine::Services::get().getGraphics()->setRenderTarget(&_renderTarget);
}

void Fade::unsetTarget()
{
    LeoEngine::Services::get().getGraphics()->setRenderTarget(nullptr);
}

void Fade::fade(FadeDirection fadeDirection, double fadeSeconds)
{
    _fadeDirection = fadeDirection;
    _fadeSeconds = fadeSeconds;

    _elapsedSeconds = 0.0;
}

bool Fade::update(double deltaTime)
{
    _elapsedSeconds += deltaTime;

    switch (_fadeDirection)
    {
    case FadeDirection::IN:
        _opacity = _elapsedSeconds / _fadeSeconds;
        if (_opacity > 1.0)
        {
            _opacity = 1.0;
        }
        break;
    case FadeDirection::OUT:
        _opacity = 1 - _elapsedSeconds / _fadeSeconds;
        if (_opacity < 0.0)
        {
            _opacity = 0.0;
        }
        break;
    }

    if (_elapsedSeconds >= _fadeSeconds)
    {
        return true;
    }
    return false;
}

