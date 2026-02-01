#include "LeoEngine/Services.hpp"
#include "LeoEngine/Audio.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Collision.hpp"
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
}

void SceneLevel::onActivate()
{
    _level = GameState::getCurrentLevel();
    _level->reset();

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

    LeoEngine::Services::get().getAudio()->stopTrack(_musicTrackID, 1.0);
}

void SceneLevel::_handleFailure()
{
    GameState::addTime(FAILURE_DELTA_TIME);
}

void SceneLevel::_updateRunning(double deltaTime)
{
    static constexpr double BPM_TIMER_MULTIPLIER = ((110.0/3.0)*2.0)/60;

    GameState::addTime(-deltaTime * BPM_TIMER_MULTIPLIER);
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

    _level->update(deltaTime);
}

void SceneLevel::_updateGameOver(double deltaTime)
{

}

void SceneLevel::_updateVictory(double deltaTime)
{

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
    _level->getTarget()->draw();
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

