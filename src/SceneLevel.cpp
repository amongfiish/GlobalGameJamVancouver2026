#include "LeoEngine/Services.hpp"
#include "LeoEngine/Audio.hpp"
#include "SceneLevel.hpp"
#include "GameState.hpp"

#include "Level.hpp"

SceneLevel::SceneLevel()
    : _level(nullptr),
      _state(State::RUNNING)
{
    _backgroundMusic = LeoEngine::Services::get().getAudio()->getSound("background.wav", false);
    _musicTrackID = LeoEngine::Services::get().getAudio()->createTrack();
    LeoEngine::Services::get().getAudio()->setTrackSound(_musicTrackID, _backgroundMusic);

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

    _timerTextBox.draw();
}

void SceneLevel::onActivate()
{
    _level = GameState::getCurrentLevel();
    _level->reset();
    std::vector<Dancer::Type> types = { Dancer::Type::COLOMBINA, Dancer::Type::GATTO, Dancer::Type::JESTER, Dancer::Type::MEDICO, Dancer::Type::VOLTO };
    _level->randomizeDancerTypes(types);
    _level->setTargetType(Dancer::Type::BAUTA);
    _level->setTarget(0);

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
}

void SceneLevel::_drawGameOver()
{

}

void SceneLevel::_drawVictory()
{

}

void SceneLevel::_initializeTimerTextBox()
{
    static const std::string FONT_FILENAME = "FreeSerif.ttf";
    static const LeoEngine::Colour TEXT_COLOUR(0xff, 0xff, 0xff, 0xff);
    static int TEXT_SIZE = 50;

    _timerTextBox.setFontFilename(FONT_FILENAME);
    _timerTextBox.setText("00");
    _timerTextBox.setTextSize(TEXT_SIZE);
    _timerTextBox.setTextColour(TEXT_COLOUR);
    _timerTextBox.setOrigin(LeoEngine::UIAnchor::TOP_MIDDLE);
    _timerTextBox.setPosition(Level::DANCE_FLOOR_START_X/2, 0);
}

void SceneLevel::_updateTimerText()
{
    _timerTextBox.setText(std::to_string(static_cast<int>(GameState::getTime())));
}

