#include <memory>
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/EventChangeScene.hpp"
#include "LeoEngine/Animation.hpp"
#include "LeoEngine/SpriteStatic.hpp"
#include "SceneMainMenu.hpp"

SceneMainMenu::SceneMainMenu()
{
    std::shared_ptr<LeoEngine::Animation> mainMenuAnimation = LeoEngine::createAnimationFromStripData("main_menu.png", 384, 256, 2, 0.5);
    _backgroundSprite.setAnimation(mainMenuAnimation);
}

SceneMainMenu::~SceneMainMenu()
{

}

void SceneMainMenu::update(double deltaTime)
{
    _backgroundSprite.update(deltaTime);

    if (LeoEngine::Services::get().getInput()->getMouseButtonState(1) == LeoEngine::KeyState::PRESSED)
    {
        LeoEngine::EventChangeScene changeSceneEvent(1, 1.0);
        LeoEngine::Event* event = static_cast<LeoEngine::Event*>(&changeSceneEvent);
        LeoEngine::Services::get().getEvents()->broadcast(event);
    }
}

void SceneMainMenu::draw()
{
    _backgroundSprite.draw();
}

