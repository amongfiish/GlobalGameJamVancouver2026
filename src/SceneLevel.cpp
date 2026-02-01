#include "LeoEngine/Services.hpp"
#include "LeoEngine/Audio.hpp"
#include "SceneLevel.hpp"
#include "GameState.hpp"

#include "Level.hpp"

SceneLevel::SceneLevel()
    : _level(nullptr)
{
    _backgroundMusic = LeoEngine::Services::get().getAudio()->getSound("background.wav", false);
    _musicTrackID = LeoEngine::Services::get().getAudio()->createTrack();
    LeoEngine::Services::get().getAudio()->setTrackSound(_musicTrackID, _backgroundMusic);
}

SceneLevel::~SceneLevel()
{

}

void SceneLevel::update(double deltaTime)
{
    _level->update(deltaTime);
}

void SceneLevel::draw()
{
    _level->draw();
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

