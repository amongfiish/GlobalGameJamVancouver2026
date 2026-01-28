#include "LeoEngine/Engine.hpp"
#include "LeoEngine/Game.hpp"
#include "LeoEngine/SceneCollection.hpp"
#include "LeoEngine/File.hpp"
#include "LeoEngine/SceneTest.hpp"

int main(int argc, char* argv[])
{
    LeoEngine::Engine leoEngine;
    LeoEngine::Game game;

    leoEngine.setFramerate(60);
    LeoEngine::Services::get().getGraphics()->setWindowTitle("GlobalGameJamVancouver2026");
    LeoEngine::Services::get().getGraphics()->setWindowDimensions(800, 800);
    LeoEngine::Services::get().getGraphics()->setRenderDimensions(200, 200);
    LeoEngine::Services::get().getGraphics()->setWindowBordered(true);
    LeoEngine::Services::get().getGraphics()->setWindowFullscreen(false);
    LeoEngine::Services::get().getGraphics()->setWindowResizable(true);
    LeoEngine::Services::get().getGraphics()->setWindowGrabCursor(false);
    LeoEngine::File::setWriteDirectory("TurboCity", "GlobalGameJameVancouver2026");

    LeoEngine::SceneCollection& gameSceneCollection = game.getSceneCollection();
    int testSceneID = gameSceneCollection.addScene<LeoEngine::SceneTest>();

    gameSceneCollection.setCurrentScene(testSceneID);

    leoEngine.runGame(game);
}

