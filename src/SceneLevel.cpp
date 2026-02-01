#include "LeoEngine/Services.hpp"
#include "LeoEngine/Audio.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Collision.hpp"
#include "LeoEngine/Colour.hpp"
#include "SceneLevel.hpp"
#include "GameState.hpp"

SceneLevel::SceneLevel()
    : _level(nullptr),
      _state(State::RUNNING)
{
    _backgroundMusic = LeoEngine::Services::get().getAudio()->getSound("background.wav", false);
    _musicTrackID = LeoEngine::Services::get().getAudio()->createTrack();
    LeoEngine::Services::get().getAudio()->setTrackSound(_musicTrackID, _backgroundMusic);

    _sidebarBackgroundSprite.setTextureFilename("sidebar.png");
    _sidebarBackgroundSprite.setPosition(Level::BACKGROUND_WIDTH, 0);
    _sidebarBackgroundSprite.setSize(128, Level::BACKGROUND_HEIGHT);

    _targetPortrait.getSprite().setPosition(_TARGET_PORTRAIT_X, _TARGET_PORTRAIT_Y);
    _targetPortrait.getSprite().setSize(Dancer::SIZE, Dancer::SIZE);

    _gameOverAnimation = LeoEngine::createAnimationFromStripData("game_over.png", 256, 256, 3, 1.0);

    _initializeTimerTextBox();     
}

SceneLevel::~SceneLevel()
{

}

void SceneLevel::update(double deltaTime)
{
    switch (_state)
    {
    case State::RUNNING:
        _updateRunning(deltaTime);
        break;
    case State::GAME_OVER:
        _updateGameOver(deltaTime);
        break;
    case State::VICTORY:
        _updateVictory(deltaTime);
        break;
    }
}

void SceneLevel::draw()
{
    switch (_state)
    {
    case State::RUNNING:
        _drawRunning();
        break;
    case State::GAME_OVER:
        _drawGameOver();
        break;
    case State::VICTORY:
        _drawVictory();
        break;
    }

    _sidebarBackgroundSprite.draw();
    _timerTextBox.draw();

    _targetPortrait.draw();
}

void SceneLevel::onActivate()
{
    _level = GameState::getCurrentLevel();
    _level->reset();

    _targetPortrait.setAnimation(Dancer::IDLE_ANIMATIONS[static_cast<int>(_level->getTarget()->getType())]);

    GameState::resetTime();

    LeoEngine::Services::get().getAudio()->playTrack(_musicTrackID, -1, 1.0);
}

void SceneLevel::onDeactivate()
{
    _level = nullptr;

    LeoEngine::Services::get().getAudio()->stopTrack(_musicTrackID, 1.0);
}

void SceneLevel::_handleGameOver()
{
    _state = State::GAME_OVER;

    LeoEngine::Services::get().getAudio()->stopTrack(_musicTrackID, 0);
}

void SceneLevel::_handleVictory()
{
    _state = State::VICTORY;

    GameState::addTime(VICTORY_DELTA_TIME);
    _updateTimerText();

    _unmaskAnimationElapsedTime = 0.0;
    _animationSprite.setAnimation(Dancer::VICTORY_ANIMATIONS[static_cast<int>(_level->getTarget()->getType())]);
    _animationSprite.setLoop(false);
    _animationSprite.setCurrentFrame(0);
    LeoEngine::Pair<int, int> targetPosition = _level->getTarget()->getAbsolutePosition();
    _animationSprite.getSprite().setPosition(targetPosition.first, targetPosition.second);
    _animationSprite.getSprite().setSize(Dancer::SIZE, Dancer::SIZE);

    LeoEngine::Services::get().getAudio()->stopTrack(_musicTrackID, 1.0);
}

void SceneLevel::_handleFailure()
{
    GameState::addTime(FAILURE_DELTA_TIME);
}

void SceneLevel::_updateRunning(double deltaTime)
{
    static constexpr double BPM_TIMER_MULTIPLIER = ((110.0/3.0)*2.0)/60;

    double speedMultiplier = 1.0 * pow(1.01, GameState::getLevel());
    GameState::addTime(-deltaTime * BPM_TIMER_MULTIPLIER * speedMultiplier);
    int time = GameState::getTime();
    if (time <= 0)
    {
        // reset timer to 0 (for visual purposes mainly)
        GameState::addTime(-time);
        _handleGameOver();
    }
    _updateTimerText();

    if (LeoEngine::Services::get().getInput()->getMouseButtonState(1) == LeoEngine::KeyState::PRESSED)
    {
        const LeoEngine::Pair<int, int>& clickPosition = LeoEngine::Services::get().getInput()->getMousePosition();
        LeoEngine::Rectangle<int> targetBounds = _level->getTargetBounds();

        if (LeoEngine::checkForOverlap(clickPosition, targetBounds))
        {
            _handleVictory();
        }
        else
        {
            _handleFailure();
        }
    }

    _level->setSpeedMultiplier(speedMultiplier);
    _level->update(deltaTime);
}

void SceneLevel::_updateGameOver(double deltaTime)
{

}

void SceneLevel::_updateVictory(double deltaTime)
{
    _animationSprite.update(deltaTime);

    _unmaskAnimationElapsedTime += deltaTime;
    if (_unmaskAnimationElapsedTime >= _UNMASK_DURATION)
    {
        // set next level
        GameState::nextLevel();
        _state = State::RUNNING;
        _animationSprite.setAnimation(nullptr);

        _level = GameState::getCurrentLevel();
        _level->reset();
        LeoEngine::Services::get().getAudio()->playTrack(_musicTrackID, -1, 1.0);

        _targetPortrait.setAnimation(Dancer::IDLE_ANIMATIONS[static_cast<int>(_level->getTarget()->getType())]);
    }
}

void SceneLevel::_drawRunning()
{
    _level->draw();

    LeoEngine::Rectangle<int> targetBounds = _level->getTargetBounds();
    LeoEngine::Services::get().getGraphics()->drawRectangle(LeoEngine::Colour(0xff, 0xff, 0xff, 0xff), false, targetBounds);
}

void SceneLevel::_drawGameOver()
{

}

void SceneLevel::_drawVictory()
{
    static LeoEngine::Colour backgroundColour(0x30, 0x11, 0x2f, 0xff);

    LeoEngine::Services::get().getGraphics()->fill(backgroundColour);
    _animationSprite.draw();
}

void SceneLevel::_initializeTimerTextBox()
{
    static constexpr int ORIGIN_X = Level::BACKGROUND_WIDTH + 64;
    static constexpr int ORIGIN_Y = 82;
    static constexpr int TEXT_SIZE = 20;
    static const std::string FONT_FILENAME = "FreeSerif.ttf";
    static const LeoEngine::Colour TEXT_COLOUR(0xff, 0xff, 0xff, 0xff);

    _timerTextBox.setFontFilename(FONT_FILENAME);
    _timerTextBox.setText("00");
    _timerTextBox.setTextSize(TEXT_SIZE);
    _timerTextBox.setTextColour(TEXT_COLOUR);
    _timerTextBox.setOrigin(LeoEngine::UIAnchor::TOP_MIDDLE);
    _timerTextBox.setPosition(ORIGIN_X, ORIGIN_Y);
}

void SceneLevel::_updateTimerText()
{
    _timerTextBox.setText(std::to_string(static_cast<int>(GameState::getTime())));
}

