#include "SceneTest.hpp"

SceneTest::SceneTest()
{

}

SceneTest::~SceneTest()
{

}

void SceneTest::update(double deltaTime)
{
    for (auto& c : _characters)
    {
        c->update(deltaTime);
    }
}

void SceneTest::draw()
{
    for (auto& c : _characters)
    {
        c->draw();
    }
}

void SceneTest::addCharacter(Character* character)
{
    _characters.emplace_back(character);
}

