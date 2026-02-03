#include "LeoEngine/Services.hpp"
#include "LeoEngine/Audio.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Collision.hpp"
#include "LeoEngine/Colour.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/EventChangeScene.hpp"
#include "SceneLevel.hpp"
#include "GameState.hpp"
#include "numeris_romanis.hpp"

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

    _cursorSprite.setTextureFilename("cursor.png");
    _cursorSprite.setSize(_CURSOR_SIZE, _CURSOR_SIZE);

    _gameOverTransitionAnimation = LeoEngine::createAnimationFromStripData("game_over_transition.png", 256, 256, 2, 1.0);
    _gameOverInstructionAnimation = LeoEngine::createAnimationFromStripData("game_over.png", 256, 256, 2, 0.5);

    _initializeTimerTextBox();     
    _initializeLevelCountTextBox();
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

    for (auto it = _notifications.begin(); it != _notifications.end();)
    {
        if (it->update(deltaTime))
        {
            it = _notifications.erase(it);
        }
        else
        {
            it++;
        }
    }

    const LeoEngine::Pair<int, int>& mousePosition = LeoEngine::Services::get().getInput()->getMousePosition();
    _cursorSprite.setPosition(mousePosition.first - _CURSOR_SIZE/2, mousePosition.second - _CURSOR_SIZE/2);
}

void SceneLevel::draw()
{
    static LeoEngine::Colour backgroundColour(0x30, 0x11, 0x2f, 0xff);
    LeoEngine::Services::get().getGraphics()->drawRectangle(backgroundColour, true, Level::BACKGROUND_START_X, Level::BACKGROUND_START_Y, Level::BACKGROUND_WIDTH, Level::BACKGROUND_HEIGHT);

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
    _levelCountTextBox.draw();
    _timerTextBox.draw();
    _targetPortrait.draw();

    for (auto& notification : _notifications)
    {
        notification.draw();
    }

    _cursorSprite.draw();
}

void SceneLevel::onActivate()
{
    _state = State::RUNNING;

    _level = GameState::getCurrentLevel();
    _level->reset();

    _targetPortrait.setAnimation(Dancer::IDLE_ANIMATIONS[static_cast<int>(_level->getTarget()->getType())]);

    GameState::resetTime();

    LeoEngine::Services::get().getAudio()->playTrack(_musicTrackID, -1, 1.0);

    _updateLevelCountText();

    LeoEngine::Services::get().getGraphics()->hideCursor();
}

void SceneLevel::onDeactivate()
{
    _level = nullptr;

    LeoEngine::Services::get().getAudio()->stopTrack(_musicTrackID, 1.0);

    LeoEngine::Services::get().getGraphics()->showCursor();
}

void SceneLevel::fireNotification(const LeoEngine::Pair<double, double>& initialPosition, std::string text)
{
    _notifications.emplace_back(initialPosition, text);
}

void SceneLevel::_handleGameOver()
{
    _state = State::GAME_OVER;

    _gameOverAnimationElapsedTime = 0.0;
    _animationSprite.setAnimation(_gameOverTransitionAnimation);
    _animationSprite.setLoop(false);
    _animationSprite.setCurrentFrame(0);
    _animationSprite.getSprite().setPosition(0, 0);
    _animationSprite.getSprite().setSize(256, 256);

    _gameOverAnimationElapsedTime = 0.0;

    LeoEngine::Services::get().getInput()->lockInput();

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

    //LeoEngine::Services::get().getAudio()->stopTrack(_musicTrackID, 1.0);
    LeoEngine::Services::get().getAudio()->playOneShot("victory.wav");
}

void SceneLevel::_handleFailure()
{
    GameState::addTime(FAILURE_DELTA_TIME);
    
    LeoEngine::Services::get().getAudio()->playOneShot("failure.wav");
}

void SceneLevel::_updateRunning(double deltaTime)
{
    static constexpr double BPM_TIMER_MULTIPLIER = ((110.0/3.0)*2.0)/60;

    double speedMultiplier = 1.0 * pow(1.02, GameState::getLevel());
    if (GameState::getLevel() > 0)
    {
        GameState::addTime(-deltaTime * BPM_TIMER_MULTIPLIER * speedMultiplier);
    }

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

        LeoEngine::Pair<double, double> doubleClickPosition(static_cast<double>(clickPosition.first), static_cast<double>(clickPosition.second));

        if (LeoEngine::checkForOverlap(clickPosition, targetBounds))
        {
            _handleVictory();
            fireNotification(doubleClickPosition, "+" + std::to_string(static_cast<int>(VICTORY_DELTA_TIME)));
        }
        else
        {
            _handleFailure();
            fireNotification(doubleClickPosition, "-" + std::to_string(static_cast<int>(FAILURE_DELTA_TIME)));
        }
    }

    _level->setSpeedMultiplier(speedMultiplier);
    _level->update(deltaTime);
}

void SceneLevel::_updateGameOver(double deltaTime)
{
    _animationSprite.update(deltaTime);

    if (_gameOverAnimationElapsedTime == 0)
    {
        LeoEngine::Services::get().getAudio()->playOneShot("game_over.wav");
    }

    if (_gameOverAnimationElapsedTime >= _GAME_OVER_INPUT_LOCK_DURATION && !_inputUnlockedAlready)
    {
        LeoEngine::Services::get().getInput()->unlockInput();
        _inputUnlockedAlready = true;
    }
    else if (_gameOverAnimationElapsedTime >= 0)
    {
        _gameOverAnimationElapsedTime += deltaTime;
    }

    if (_gameOverAnimationElapsedTime >= _GAME_OVER_TRANSITION_DURATION)
    {
        _animationSprite.setAnimation(_gameOverInstructionAnimation);
        _animationSprite.restartAnimation();
        _animationSprite.setLoop(true);

        _gameOverAnimationElapsedTime = -1;
    }
    
    if (LeoEngine::Services::get().getInput()->getMouseButtonState(1) == LeoEngine::KeyState::PRESSED)
    {
        LeoEngine::EventChangeScene changeSceneEvent(0, 1.0);
        LeoEngine::Event* event = static_cast<LeoEngine::Event*>(&changeSceneEvent);
        
        LeoEngine::Services::get().getEvents()->broadcast(event);
    }
}

void SceneLevel::_updateVictory(double deltaTime)
{
    _animationSprite.update(deltaTime);

    _unmaskAnimationElapsedTime += deltaTime;
    if (_unmaskSFXTimer >= _UNMASK_SFX_DELAY)
    {
        _unmaskSFXTimer = -1;
        LeoEngine::Services::get().getAudio()->playOneShot("unmasking.wav");
    }
    else if (_unmaskSFXTimer >= 0)
    {
        _unmaskSFXTimer += deltaTime;
    }

    if (_unmaskAnimationElapsedTime >= _UNMASK_DURATION)
    {
        // set next level
        GameState::nextLevel();
        _state = State::RUNNING;
        _animationSprite.setAnimation(nullptr);

        _level = GameState::getCurrentLevel();
        _level->reset();

        _targetPortrait.setAnimation(Dancer::IDLE_ANIMATIONS[static_cast<int>(_level->getTarget()->getType())]);

        _updateLevelCountText();
        _unmaskSFXTimer = 0.0;
    }
}

void SceneLevel::_drawRunning()
{
    _level->draw();

    /*
    LeoEngine::Rectangle<int> targetBounds = _level->getTargetBounds();
    LeoEngine::Services::get().getGraphics()->drawRectangle(LeoEngine::Colour(0xff, 0xff, 0xff, 0xff), false, targetBounds);
    */
}

void SceneLevel::_drawGameOver()
{
    _animationSprite.draw();
}

void SceneLevel::_drawVictory()
{
    _animationSprite.draw();
}

void SceneLevel::_initializeTimerTextBox()
{
    static constexpr int ORIGIN_X = Level::BACKGROUND_WIDTH + 64;
    static constexpr int ORIGIN_Y = 82;
    static constexpr int TEXT_SIZE = 20;
    static const std::string FONT_FILENAME = "FreeSerif.ttf";
    static const LeoEngine::Colour TEXT_COLOUR(0xcd, 0xb0, 0x86, 0xff);

    _timerTextBox.setFontFilename(FONT_FILENAME);
    _timerTextBox.setText("0");
    _timerTextBox.setTextSize(TEXT_SIZE);
    _timerTextBox.setTextColour(TEXT_COLOUR);
    _timerTextBox.setOrigin(LeoEngine::UIAnchor::TOP_MIDDLE);
    _timerTextBox.setPosition(ORIGIN_X, ORIGIN_Y);
}

void SceneLevel::_updateTimerText()
{
    _timerTextBox.setText(std::to_string(static_cast<int>(GameState::getTime())));
}

void SceneLevel::_initializeLevelCountTextBox()
{
    static constexpr int ORIGIN_X = Level::BACKGROUND_WIDTH + 64;
    static constexpr int ORIGIN_Y = 8;
    static constexpr int TEXT_SIZE = 15;
    static const std::string FONT_FILENAME = "FreeSerif.ttf";
    static const LeoEngine::Colour TEXT_COLOUR(0x00, 0x00, 0x00, 0xff);

    _levelCountTextBox.setFontFilename(FONT_FILENAME);
    _levelCountTextBox.setText("Turbo City Games");
    _levelCountTextBox.setTextSize(TEXT_SIZE);
    _levelCountTextBox.setTextColour(TEXT_COLOUR);
    _levelCountTextBox.setOrigin(LeoEngine::UIAnchor::TOP_MIDDLE);
    _levelCountTextBox.setPosition(ORIGIN_X, ORIGIN_Y);
}

void SceneLevel::_updateLevelCountText()
{
    int level = GameState::getLevel();

    _levelCountTextBox.setText(rom::numerus(static_cast<long long unsigned int>(level+1)).ad_filum());
}

