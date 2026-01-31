#include <cmath>
#include "SceneTesting.hpp"

SceneTesting::SceneTesting()
{
    for (int i = 0; i < 10; i++)
    {
        _dancers.emplace_back(Dancer::Type::DANCER_A, [](double t){ return LeoEngine::Pair<double, double>(0.7*cos(t), -0.7*sin(t)); }, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(1.0, 1.0), i*(M_PI/5), 1.0);
    }
}

SceneTesting::~SceneTesting()
{

}

void SceneTesting::update(double deltaTime)
{
    for (auto& dancer : _dancers)
    {
        dancer.update(deltaTime);
    }
}

void SceneTesting::draw()
{
    for (auto& dancer : _dancers)
    {
        dancer.draw();
    }
}

