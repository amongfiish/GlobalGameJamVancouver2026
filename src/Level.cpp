#include <string>
#include <cmath>
#include "LeoEngine/RandomNumberGenerator.hpp"
#include "Level.hpp"
#include "GameState.hpp"

LeoEngine::SpriteStatic Level::_backgroundSprite = _makeBackgroundSprite();


Level::Level()
    : _targetType(static_cast<Dancer::Type>(0)),
      _speedMultiplier(1.0)
{
    _initializeTimerTextBox();     
}

Level::~Level()
{

}

void Level::update(double deltaTime)
{
    static constexpr double BPM_TIMER_MULTIPLIER = ((110.0/3.0)*2.0)/60;

    for (int i = 0; i < _dancers.size(); i++)
    {
        _dancers.at(i).update(deltaTime);
        reSortDancerByY(_dancers, i);
    }

    GameState::addTime(-deltaTime * BPM_TIMER_MULTIPLIER);
    _timerTextBox.setText(std::to_string(static_cast<int>(GameState::getTime())));
}

void Level::draw()
{
    _backgroundSprite.draw();

    for (int i = 0; i < _dancers.size(); i++)
    {
        _dancers.at(i).draw();
    }

    _timerTextBox.draw();
}

void Level::reset()
{
    GameState::resetTime();

    for (auto& dancer : _dancers)
    {
        dancer.reset();
    }
}

void Level::setSpeedMultiplier(double speedMultiplier)
{
    _speedMultiplier = speedMultiplier;
    for (auto& dancer : _dancers)
    {
        dancer.setLevelSpeedMultiplier(_speedMultiplier);
    }
}

void Level::setTargetType(Dancer::Type targetType)
{
    _targetType = targetType;
    _dancers.at(_target).setType(targetType);
}

void Level::randomizeDancerTypes(std::vector<Dancer::Type> types)
{
    static LeoEngine::RandomNumberGenerator rng;

    for (auto& dancer : _dancers)
    {
        dancer.setType(types.at(rng.getNextNumber(0, types.size()-1)));
    }
}

void Level::setTarget(int i)
{
    _target = i;
    _dancers.at(i).setType(_targetType);
}

std::vector<Dancer>& Level::getDancers()
{
    return _dancers;
}

void Level::addDancer(Dancer&& dancer)
{
    _dancers.emplace_back(dancer);

    int newDancerIndex = _dancers.size() - 1;
    _dancers.at(newDancerIndex).setLevelSpeedMultiplier(_speedMultiplier);
    reSortDancerByY(_dancers, newDancerIndex);
}

LeoEngine::SpriteStatic Level::_makeBackgroundSprite()
{
    LeoEngine::SpriteStatic sprite("background.png");
    sprite.setPosition(BACKGROUND_START_X, BACKGROUND_START_Y);
    sprite.setSize(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    return sprite;
}

void Level::_initializeTimerTextBox()
{
    static const std::string FONT_FILENAME = "FreeSerif.ttf";
    static const LeoEngine::Colour TEXT_COLOUR(0xff, 0xff, 0xff, 0xff);
    static int TEXT_SIZE = 50;

    _timerTextBox.setFontFilename(FONT_FILENAME);
    _timerTextBox.setText("00");
    _timerTextBox.setTextSize(TEXT_SIZE);
    _timerTextBox.setTextColour(TEXT_COLOUR);
    _timerTextBox.setOrigin(LeoEngine::UIAnchor::TOP_MIDDLE);
    _timerTextBox.setPosition(DANCE_FLOOR_START_X/2, 0);
}

