// Blood Gala
// Copyright (C) 2026 TurboCity
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
    LeoEngine::Services::get().getGraphics()->setWindowTitle("Blood Gala");
    LeoEngine::Services::get().getGraphics()->setWindowDimensions(1152, 768);
    LeoEngine::Services::get().getGraphics()->setRenderDimensions(384, 256);
    LeoEngine::Services::get().getGraphics()->setWindowBordered(true);
    LeoEngine::Services::get().getGraphics()->setWindowFullscreen(false);
    LeoEngine::Services::get().getGraphics()->setWindowResizable(true);
    LeoEngine::Services::get().getGraphics()->setWindowGrabCursor(false);
    LeoEngine::Services::get().getGraphics()->setRenderVSync(false);
    LeoEngine::Services::get().getGraphics()->setWindowIcon("icon.png");
    LeoEngine::File::setWriteDirectory("TurboCity", "BloodGala");

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

