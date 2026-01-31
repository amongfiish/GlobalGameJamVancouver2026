#ifndef SCENE_TESTING_HPP
#define SCENE_TESTING_HPP

#include <vector>
#include "LeoEngine/Scene.hpp"
#include "Dancer.hpp"

class SceneTesting : public LeoEngine::Scene
{
public:
    SceneTesting();
    ~SceneTesting();

    virtual void update(double deltaTime) override;
    virtual void draw() override;

    virtual void onActivate() override {}
    virtual void onDeactivate() override {}

private:
    std::vector<Dancer> _dancers;
};

#endif

