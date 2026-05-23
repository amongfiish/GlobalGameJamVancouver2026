#ifndef SCENE_MAIN_MENU_HPP
#define SCENE_MAIN_MENU_HPP

#include "LeoEngine/Scene.hpp"
#include "LeoEngine/SpriteAnimated.hpp"

class SceneMainMenu : public LeoEngine::Scene
{
public:
    SceneMainMenu();
    virtual ~SceneMainMenu();

    virtual void update(double deltaTime) override;
    virtual void draw() override;

    virtual void onActivate() override {};
    virtual void onDeactivate() override {};

private:
    LeoEngine::SpriteAnimated _backgroundSprite;
};

#endif

