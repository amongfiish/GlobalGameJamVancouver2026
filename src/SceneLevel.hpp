#ifndef SCENE_LEVEL_HPP
#define SCENE_LEVEL_HPP

#include <memory>
#include "LeoEngine/Scene.hpp"
#include "LeoEngine/Sound.hpp"
#include "LeoEngine/UIText.hpp"
#include "LeoEngine/SpriteStatic.hpp"
#include "LeoEngine/SpriteAnimated.hpp"
#include "Level.hpp"

class Notification
{
public:
    Notification(const LeoEngine::Pair<double, double>& initialPosition, std::string text)
        : _renderedText(nullptr),
          _position(initialPosition),
          _elapsedTime(0.0)
    {
        LeoEngine::TextDrawData textDrawData("FreeSerif.ttf", 10, LeoEngine::Colour(0xff, 0xff, 0xff, 0xff));
        _renderedText = LeoEngine::Services::get().getGraphics()->renderText(text, textDrawData);

        LeoEngine::RandomNumberGenerator rng;
        _velocity.first = static_cast<double>(rng.getNextNumber(10, 30) - 20);
        _velocity.second = static_cast<double>(-rng.getNextNumber(5, 10));
    }

    ~Notification()
    {

    }

    bool update(double deltaTime)
    {
        _position.first += _velocity.first * deltaTime;
        _position.second += _velocity.second * deltaTime;

        _elapsedTime += deltaTime;
        if (_elapsedTime > _DISPLAY_TIME)
        {
            return true;
        }

        return false;
    }

    void draw()
    {
        LeoEngine::Pair<int, int> intPosition(static_cast<int>(_position.first), static_cast<int>(_position.second));
        LeoEngine::Services::get().getGraphics()->drawTexture(*_renderedText, LeoEngine::TextureDrawData(nullptr, std::make_shared<LeoEngine::Rectangle<int>>(intPosition, _renderedText->getDimensions()), 0.0, nullptr, LeoEngine::FlipType::NONE));
    }

private:
    static constexpr double _DISPLAY_TIME = 1.0;
    double _elapsedTime;

    LeoEngine::Pair<double, double> _position;
    LeoEngine::Pair<double, double> _velocity;

    std::shared_ptr<LeoEngine::Texture> _renderedText;
};

class SceneLevel : public LeoEngine::Scene
{
public:
    enum class State 
    {
        RUNNING,
        GAME_OVER,
        VICTORY 
    };

    SceneLevel();
    virtual ~SceneLevel();

    virtual void update(double deltaTime) override;
    virtual void draw() override;;

    virtual void onActivate() override;
    virtual void onDeactivate() override;

    void fireNotification(const LeoEngine::Pair<double, double>& initialPosition, std::string text);

    static constexpr double VICTORY_DELTA_TIME = 5.0;
    static constexpr double FAILURE_DELTA_TIME = -10.0;

private:
    static constexpr int _TARGET_PORTRAIT_X = 304;
    static constexpr int _TARGET_PORTRAIT_Y = 158;

    std::vector<Notification> _notifications;

    std::shared_ptr<LeoEngine::Animation> _gameOverAnimation;
    
    LeoEngine::SpriteAnimated _animationSprite;
    LeoEngine::SpriteAnimated _targetPortrait;

    // when the timer runs out
    void _handleGameOver();
    // when the player clicks the right character
    void _handleVictory();
    // when the player clicks the wrong character
    void _handleFailure();

    void _updateRunning(double deltaTime);
    void _updateGameOver(double deltaTime);
    void _updateVictory(double deltaTime);

    void _drawRunning();
    void _drawGameOver();
    void _drawVictory();

    State _state;

    LeoEngine::UIText _timerTextBox;
    void _initializeTimerTextBox();
    void _updateTimerText();

    LeoEngine::UIText _levelCountTextBox;
    void _initializeLevelCountTextBox();
    void _updateLevelCountText();

    LeoEngine::SpriteStatic _sidebarBackgroundSprite;

    std::shared_ptr<Level> _level;
    
    LeoEngine::Sound* _backgroundMusic;
    int _musicTrackID;

    // game over/victory
    static constexpr double _UNMASK_DURATION = 2.8;
    static constexpr double _UNMASK_SFX_DELAY = 1.0;
    double _unmaskAnimationElapsedTime;
    double _unmaskSFXTimer;

    static constexpr double _GAME_OVER_DURATION = 3.0;
    double _gameOverAnimationElapsedTime;
};

#endif

