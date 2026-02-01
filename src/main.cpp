#include "LeoEngine/Engine.hpp"
#include "LeoEngine/Game.hpp"
#include "LeoEngine/SceneCollection.hpp"
#include "LeoEngine/File.hpp"
#include "GameState.hpp"
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
    LeoEngine::Services::get().getGraphics()->setRenderVSync(false);
    LeoEngine::File::setWriteDirectory("TurboCity", "GlobalGameJameVancouver2026");

    LeoEngine::SceneCollection& gameSceneCollection = game.getSceneCollection();
    int menuSceneID = gameSceneCollection.addScene<SceneMainMenu>();
    int gameSceneID = gameSceneCollection.addScene<SceneLevel>();

    GameState::setCurrentLevel(Levels::makeTutorial());

    gameSceneCollection.setCurrentScene(menuSceneID);

    leoEngine.runGame(game);
}

