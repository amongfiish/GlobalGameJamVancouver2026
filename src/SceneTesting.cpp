#include "SceneTesting.hpp"

SceneTesting::SceneTesting()
    : _testDancer(Dancer::Type::DANCER_A, [](int t) { return LeoEngine::Pair<int, int>(0, 0); }, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0)
{

}

SceneTesting::~SceneTesting()
{

}

void SceneTesting::update(double deltaTime)
{
    _testDancer.update(deltaTime);
}

void SceneTesting::draw()
{
    _testDancer.draw();
}

