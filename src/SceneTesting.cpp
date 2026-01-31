#include <cmath>
#include "SceneTesting.hpp"

SceneTesting::SceneTesting()
{
    for (int i = 0; i < 20; i++)
    {
        _dancers.emplace_back(Dancer::Type::DANCER_A, [](double t){ return LeoEngine::Pair<double, double>(0.7*cos(t), -0.7*sin(t)); }, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(0.5, 0.4), i*((2*M_PI)/20), 1.0);
        _dancers.at(i).update(0);

        reSortDancerByY(_dancers, i);
    }

    for (int i = 0; i < 40; i++)
    {
        _dancers.emplace_back(Dancer::Type::DANCER_A, [](double t){ return LeoEngine::Pair<double, double>(0.7*cos(t), 0.7*sin(t)); }, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(1.0, 0.8), i*((2*M_PI)/40), 1.0);
        _dancers.at(i).update(0);

        reSortDancerByY(_dancers, i);
    }

    _dancers.emplace_back(Dancer::Type::DANCER_A, [](double t){ return LeoEngine::Pair<double, double>((static_cast<int>(100*t)%200)/100.0-1, -sin(t)); }, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(1.0, 0.8), 0, 1.0);
}

SceneTesting::~SceneTesting()
{

}

void SceneTesting::update(double deltaTime)
{
    for (int i = 0; i < _dancers.size(); i++)
    {
        _dancers.at(i).update(deltaTime);

        reSortDancerByY(_dancers, i);
    }
}

void SceneTesting::draw()
{
    for (auto& dancer : _dancers)
    {
        dancer.draw();
    }
}

