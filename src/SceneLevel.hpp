#ifndef SCENE_LEVEL_HPP
#define SCENE_LEVEL_HPP

#include "LeoEngine/Scene.hpp"
#include "LeoEngine/Sound.hpp"

class Level;

class SceneLevel : public LeoEngine::Scene
{
public:
    SceneLevel();
    virtual ~SceneLevel();

    virtual void update(double deltaTime) override;
    virtual void draw() override;;

    virtual void onActivate() override;
    virtual void onDeactivate() override;

private:
    Level* _level;
    
    LeoEngine::Sound* _backgroundMusic;
    int _musicTrackID;
};

#endif

