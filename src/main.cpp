#include "LeoEngine/Engine.hpp"
#include "LeoEngine/Game.hpp"
#include "LeoEngine/SceneCollection.hpp"
#include "LeoEngine/File.hpp"
#include "SceneTesting.hpp"

int main(int argc, char* argv[])
{
    LeoEngine::Engine leoEngine;
    LeoEngine::Game game;

    leoEngine.setFramerate(120);
    LeoEngine::Services::get().getGraphics()->setWindowTitle("GlobalGameJamVancouver2026");
    LeoEngine::Services::get().getGraphics()->setWindowDimensions(768, 768);
    LeoEngine::Services::get().getGraphics()->setRenderDimensions(256, 256);
    LeoEngine::Services::get().getGraphics()->setWindowBordered(true);
    LeoEngine::Services::get().getGraphics()->setWindowFullscreen(false);
    LeoEngine::Services::get().getGraphics()->setWindowResizable(true);
    LeoEngine::Services::get().getGraphics()->setWindowGrabCursor(false);
    LeoEngine::Services::get().getGraphics()->setRenderVSync(true);
    LeoEngine::File::setWriteDirectory("TurboCity", "GlobalGameJameVancouver2026");

    LeoEngine::SceneCollection& gameSceneCollection = game.getSceneCollection();
    int testSceneID = gameSceneCollection.addScene<SceneTesting>();

    gameSceneCollection.setCurrentScene(testSceneID);

    leoEngine.runGame(game);
}

