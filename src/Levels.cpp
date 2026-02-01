#include <cmath>
#include <algorithm>
#include "Levels.hpp"
#include "DancePatterns.hpp"
#include "Dancer.hpp"

LeoEngine::RandomNumberGenerator Levels::_rng;

std::vector<Dancer::Type> generateTypeVector(Dancer::Type targetType)
{
    static std::vector<Dancer::Type> randomTypes = { Dancer::Type::BAUTA, Dancer::Type::COLOMBINA, Dancer::Type::GATTO, Dancer::Type::JESTER, Dancer::Type::MEDICO, Dancer::Type::VOLTO };

    randomTypes.erase(std::find(randomTypes.begin(), randomTypes.end(), targetType));

    return randomTypes;
}

Dancer::Type Levels::_getRandomType()
{
    static std::vector<Dancer::Type> randomTypes = { Dancer::Type::BAUTA, Dancer::Type::COLOMBINA, Dancer::Type::GATTO, Dancer::Type::JESTER, Dancer::Type::MEDICO, Dancer::Type::VOLTO };

    return randomTypes.at(_rng.getNextNumber(0,5));
}

std::vector<LeoEngine::Pair<double, double>> generateGrid(int gridSize)
{
    static constexpr double GRID_MARGIN = 0.0;
    static constexpr double GRID_SCREEN_SIZE = 2 - 2*GRID_MARGIN;
    
    const double GRID_CELL_WIDTH = GRID_SCREEN_SIZE / gridSize;

    // create vector of all available grid spaces
    std::vector<LeoEngine::Pair<double, double>> availableGridSpaces;
    for (int y = 0; y < gridSize; y++)
    {
        for (int x = 0; x < gridSize; x++)
        {
            availableGridSpaces.emplace_back(x * GRID_CELL_WIDTH - GRID_SCREEN_SIZE/2 + GRID_CELL_WIDTH/2, y * GRID_CELL_WIDTH - GRID_SCREEN_SIZE/2 + GRID_CELL_WIDTH/2);
        }
    }

    return availableGridSpaces;
}

std::unique_ptr<Level> Levels::makeTest()
{
    auto level = std::make_unique<Level>();
    level->addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    level->addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(-1.0, -1.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    level->addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(1.0, -1.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    level->addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(-1.0, 1.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    level->addDancer(Dancer(&DancePatterns::still, LeoEngine::Pair<double, double>(1.0, 1.0), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    return std::move(level);
}

std::unique_ptr<Level> Levels::makeTutorial()
{
    auto level = std::make_unique<Level>();

    Dancer dancer0(&DancePatterns::still, LeoEngine::Pair<double, double>(-0.5, -0.25), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0);
    level->addDancer(std::move(dancer0));

    Dancer dancer1(&DancePatterns::still, LeoEngine::Pair<double, double>(-0.0, -0.25), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0);
    level->addDancer(std::move(dancer1));

    Dancer dancer2(&DancePatterns::still, LeoEngine::Pair<double, double>(0.5, -0.25), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0);
    dancer2.setType(Dancer::Type::GATTO);
    level->addDancer(std::move(dancer2));

    Dancer dancer3(&DancePatterns::still, LeoEngine::Pair<double, double>(-0.5, 0.25), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0);
    dancer3.setType(Dancer::Type::JESTER);
    level->addDancer(std::move(dancer3));

    Dancer dancer4(&DancePatterns::still, LeoEngine::Pair<double, double>(-0.0, 0.25), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0);
    dancer4.setType(Dancer::Type::MEDICO);
    level->addDancer(std::move(dancer4));

    Dancer dancer5(&DancePatterns::still, LeoEngine::Pair<double, double>(0.5, 0.25), LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0);
    dancer5.setType(Dancer::Type::VOLTO);
    level->addDancer(std::move(dancer5));

    level->setTarget(_rng.getNextNumber(0,5));

    int targetType = _rng.getNextNumber(0,5);
    level->setTargetType(static_cast<Dancer::Type>(targetType));

    int nextTypeID = 0;
    for (auto& dancer : level->getDancers())
    {
        if (&dancer == level->getTarget())
        {
            continue;
        }

        if (nextTypeID == targetType)
        {
            nextTypeID++;
        }

        dancer.setType(static_cast<Dancer::Type>(nextTypeID++));
    }

    return std::move(level);
}

std::unique_ptr<Level> Levels::makeLine()
{
    static constexpr int NUMBER_OF_DANCERS = 10;

    auto level = std::make_unique<Level>();

    for (int i = 0; i < NUMBER_OF_DANCERS; i++)
    {
        level->addDancer(Dancer(&DancePatterns::linear, LeoEngine::Pair<double, double>(0.5, 0.0), LeoEngine::Pair<double, double>(1.0, 1.0), (static_cast<double>(i)/NUMBER_OF_DANCERS) * 2 - 1, 1.0));
    }

    level->randomizeDancerTypes(generateTypeVector(Dancer::Type::BAUTA));

    level->setTarget(0);
    level->setTargetType(Dancer::Type::BAUTA);

    return std::move(level);
}

std::unique_ptr<Level> Levels::makeStatic(int gridSize, int numberOfDancers)
{
    auto level = std::make_unique<Level>();
    
    std::vector<LeoEngine::Pair<double, double>> availableGridSpaces = generateGrid(gridSize);

    // choose grid spaces randomly for dancers; pop
    for (int i = 0; i < numberOfDancers; i++)
    {
        int chosenGridSlotIndex = _rng.getNextNumber(0, availableGridSpaces.size()-1);
        LeoEngine::Pair<double, double> chosenGridSlot = availableGridSpaces.at(chosenGridSlotIndex);
        availableGridSpaces.erase(availableGridSpaces.begin()+chosenGridSlotIndex);
        level->addDancer(Dancer(&DancePatterns::still, chosenGridSlot, LeoEngine::Pair<double, double>(1.0, 1.0), 0.0, 1.0));
    }

    Dancer::Type targetType = _getRandomType();
    level->randomizeDancerTypes(generateTypeVector(targetType));
    level->setTarget(_rng.getNextNumber(0, level->getDancers().size()-1));
    level->setTargetType(targetType);

    return level;
}

std::unique_ptr<Level> Levels::makeColinear(int numberOfDancers)
{
    auto level = std::make_unique<Level>();

    double angle = _rng.getNextNumber(0, 999) / 999.0 * M_PI;
    double slope = tan(angle);

    std::vector<LeoEngine::Pair<double, double>> availableGridPositions = generateGrid(16);

    for (int i = 0; i < numberOfDancers; i++)
    {
        bool movingForwards = static_cast<bool>(_rng.getNextNumber(0,1));

        int chosenGridPosition = _rng.getNextNumber(0, availableGridPositions.size()-1);
        level->addDancer(Dancer(&DancePatterns::linear, availableGridPositions.at(chosenGridPosition), LeoEngine::Pair<double, double>(1/(sqrt(1+pow(slope,2))),slope/(sqrt(1+pow(slope,2)))), 0.0, movingForwards ? 1 : -1));
    }

    Dancer::Type targetType = _getRandomType();
    level->randomizeDancerTypes(generateTypeVector(targetType));
    level->setTarget(_rng.getNextNumber(0, level->getDancers().size()-1));
    level->setTargetType(targetType);

    return level;
}

/*
Level Levels::makeStatic(int difficulty)
{
   
}

Level Levels::makeCircle()
{
    static constexpr int NUMBER_OF_DANCERS = 30;

    Level level;
    for (int i = 0; i < NUMBER_OF_DANCERS; i++)
    {
        level.addDancer(Dancer(&DancePatterns::circle, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(0.7, 0.7), (static_cast<double>(i)/NUMBER_OF_DANCERS)*M_PI*2, 1.0));
    }
    
    std::vector<Dancer::Type> randomTypes = { Dancer::Type::COLOMBINA, Dancer::Type::GATTO, Dancer::Type::JESTER, Dancer::Type::MEDICO, Dancer::Type::VOLTO };
    level.randomizeDancerTypes(randomTypes);

    level.setTarget(0);
    level.setTargetType(Dancer::Type::BAUTA);

    return level;
}
*/

