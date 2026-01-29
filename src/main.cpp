#include "LeoEngine/Engine.hpp"
#include "LeoEngine/Game.hpp"
#include "LeoEngine/SceneCollection.hpp"
#include "LeoEngine/File.hpp"
#include "LeoEngine/RandomNumberGenerator.hpp"
#include "SceneTest.hpp"
#include "CharacterFixedMovement.hpp"

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
    int testSceneID = gameSceneCollection.addScene<SceneTest>();
    SceneTest* testScene = static_cast<SceneTest*>(gameSceneCollection.getScene(testSceneID));

    LeoEngine::RandomNumberGenerator rng;

    for (int i = 0; i < 100; i++)
    {
        // testScene->addCharacter(new CharacterFixedMovement(LeoEngine::Pair<double, double>(rng.getNextNumber(0, 190), rng.getNextNumber(0, 190)), LeoEngine::Colour(rng.getNextNumber(0x55, 0xFF), rng.getNextNumber(0x55, 0xFF), rng.getNextNumber(0x55, 0xFF), 0xFF), LeoEngine::Pair<double, double>(rng.getNextNumber(50, 100) * (rng.getNextNumber(0,1)?-1:1), rng.getNextNumber(25, 75) * (rng.getNextNumber(0,1)?-1:1))));
    }

    gameSceneCollection.setCurrentScene(testSceneID);

    leoEngine.runGame(game);
}

