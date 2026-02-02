#include "LeoEngine/Engine.hpp"
#include "LeoEngine/Game.hpp"
#include "LeoEngine/SceneSplashScreen.hpp"
#include "LeoEngine/SceneCollection.hpp"
#include "LeoEngine/File.hpp"
#include "Levels.hpp"
#include "SceneMainMenu.hpp"
#include "SceneLevel.hpp"

int main(int argc, char* argv[])
{
    LeoEngine::Engine leoEngine;
    LeoEngine::Game game;

    leoEngine.setFramerate(60);
    LeoEngine::Services::get().getGraphics()->setWindowTitle("GlobalGameJamVancouver2026");
    LeoEngine::Services::get().getGraphics()->setWindowDimensions(1152, 768);
    LeoEngine::Services::get().getGraphics()->setRenderDimensions(384, 256);
    LeoEngine::Services::get().getGraphics()->setWindowBordered(true);
    LeoEngine::Services::get().getGraphics()->setWindowFullscreen(false);
    LeoEngine::Services::get().getGraphics()->setWindowResizable(true);
    LeoEngine::Services::get().getGraphics()->setWindowGrabCursor(false);
    LeoEngine::Services::get().getGraphics()->setRenderVSync(true);
    LeoEngine::File::setWriteDirectory("TurboCity", "GlobalGameJameVancouver2026");

    LeoEngine::SceneCollection& gameSceneCollection = game.getSceneCollection();

    int menuSceneID = gameSceneCollection.addScene<SceneMainMenu>();
    int gameSceneID = gameSceneCollection.addScene<SceneLevel>();
    int turboCitySplashSceneID = gameSceneCollection.addScene<LeoEngine::SceneSplashScreen>();

    // basically pulled straight from AlleyCats-Leo
    LeoEngine::Scene *turboCitySplashScene = gameSceneCollection.getScene(turboCitySplashSceneID);
    LeoEngine::SceneSplashScreen *turboCitySplashSceneCast = dynamic_cast<LeoEngine::SceneSplashScreen *>(turboCitySplashScene);
    std::shared_ptr<LeoEngine::Animation> turboCitySplashAnimation = LeoEngine::createAnimationFromStripData("turbocitysplash.png", 192, 65, 40, 0.0833);
    turboCitySplashSceneCast->setSplash(turboCitySplashAnimation, std::make_shared<LeoEngine::Rectangle<int>>(42, 75, 300, 100), 4, LeoEngine::Colour(0x00, 0x00, 0x00, 0xFF), "splash_sound.wav");
    turboCitySplashSceneCast->setNextSceneID(0);

    gameSceneCollection.setCurrentScene(turboCitySplashSceneID);

    leoEngine.runGame(game);
}

