#ifndef SCENE_LEVEL_HPP
#define SCENE_LEVEL_HPP

#include <memory>
#include "LeoEngine/Scene.hpp"
#include "LeoEngine/Sound.hpp"
#include "LeoEngine/UIText.hpp"
#include "LeoEngine/SpriteStatic.hpp"
#include "LeoEngine/SpriteAnimated.hpp"
#include "Level.hpp"

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

    static constexpr double VICTORY_DELTA_TIME = 5.0;
    static constexpr double FAILURE_DELTA_TIME = -10.0;

private:
    std::shared_ptr<LeoEngine::Animation> _gameOverAnimation;
    
    //LeoEngine::SpriteAnimated _animationSprite;

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

    LeoEngine::SpriteStatic _sidebarBackgroundSprite;

    Level* _level;
    
    LeoEngine::Sound* _backgroundMusic;
    int _musicTrackID;

    // game over/victory
    static constexpr double _UNMASK_DURATION = 2.8;
    double _unmaskAnimationElapsedTime;
};

#endif

