#ifndef SCENE_TEST_HPP
#define SCENE_TEST_HPP

#include <vector>
#include <memory>
#include "LeoEngine/Scene.hpp"
#include "Character.hpp"

class SceneTest : public LeoEngine::Scene
{
public:
    SceneTest();
    virtual ~SceneTest();

    virtual void update(double deltaTime) override;
    virtual void draw() override;

    void addCharacter(Character* character);

private:
    std::vector<std::unique_ptr<Character>> _characters;
};

#endif

