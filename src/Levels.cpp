#include <cmath>
#include <algorithm>
#include "Levels.hpp"
#include "DancePatterns.hpp"
#include "Dancer.hpp"

#if defined(_WIN32)
    #define M_PI 3.141593
#endif

LeoEngine::RandomNumberGenerator Levels::_rng;

std::function<std::unique_ptr<Level>(int)> Levels::levelMakers[] = {
    makeStatic,
    makeColinear,
    makeLinearScatter,
    makeCircle,
    makeFlower,
    makeKikibouba
};

std::vector<Dancer::Type> generateTypeVector(Dancer::Type targetType)
{
    static const std::vector<Dancer::Type> randomTypes = { Dancer::Type::BAUTA, Dancer::Type::COLOMBINA, Dancer::Type::GATTO, Dancer::Type::JESTER, Dancer::Type::MEDICO, Dancer::Type::VOLTO };

    std::vector types = randomTypes;
    types.erase(std::find(types.begin(), types.end(), targetType));

    return types;
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

std::unique_ptr<Level> Levels::makeStatic(int difficulty)
{
    auto level = std::make_unique<Level>();
    
    std::vector<LeoEngine::Pair<double, double>> availableGridSpaces = generateGrid(16);

    // choose grid spaces randomly for dancers; pop
    int numberOfDancers = 10 + 2*difficulty;
    if (numberOfDancers > 256)
    {
        numberOfDancers = 256;
    }

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

    return std::move(level);
}

std::unique_ptr<Level> Levels::makeColinear(int difficulty)
{
    auto level = std::make_unique<Level>();

    double angle = _rng.getNextNumber(0, 999) / 999.0 * M_PI;
    double slope = tan(angle);

    std::vector<LeoEngine::Pair<double, double>> availableGridPositions = generateGrid(16);

    int numberOfDancers = 8 + 2*difficulty;
    if (numberOfDancers > 256)
    {
        numberOfDancers = 256;
    }

    for (int i = 0; i < numberOfDancers; i++)
    {
        bool movingForwards = static_cast<bool>(_rng.getNextNumber(0,1));
        bool mirror = static_cast<bool>(_rng.getNextNumber(0,1));

        int chosenGridPosition = _rng.getNextNumber(0, availableGridPositions.size()-1);
        level->addDancer(Dancer(&DancePatterns::linear, availableGridPositions.at(chosenGridPosition), LeoEngine::Pair<double, double>(1/(sqrt(1+pow(slope,2))) * (mirror?-1:1),slope/(sqrt(1+pow(slope,2))) * (movingForwards?1:-1)), 0.0, 1.0));
    }

    Dancer::Type targetType = _getRandomType();
    level->randomizeDancerTypes(generateTypeVector(targetType));
    level->setTarget(_rng.getNextNumber(0, level->getDancers().size()-1));
    level->setTargetType(targetType);

    return std::move(level);
}

std::unique_ptr<Level> Levels::makeLinearScatter(int difficulty)
{
    auto level = std::make_unique<Level>();

    std::vector<LeoEngine::Pair<double, double>> availableGridPositions = generateGrid(16);

    int numberOfDancers = 8 + 2*difficulty;
    if (numberOfDancers > 256)
    {
        numberOfDancers = 256;
    }

    for (int i = 0; i < numberOfDancers; i++)
    {
        double angle = _rng.getNextNumber(0, 999) / 999.0 * M_PI;
        double slope = tan(angle);

        bool movingForwards = static_cast<bool>(_rng.getNextNumber(0,1));
        bool mirror = static_cast<bool>(_rng.getNextNumber(0,1));

        int chosenGridPosition = _rng.getNextNumber(0, availableGridPositions.size()-1);
        level->addDancer(Dancer(&DancePatterns::linear, availableGridPositions.at(chosenGridPosition), LeoEngine::Pair<double, double>(1.0/(sqrt(1+pow(slope,2))) * (mirror ? -1.0 : 1.0),slope/(sqrt(1+pow(slope,2))) * (movingForwards ? 1.0 : -1.0)), 0.0, 1.0));
    }

    Dancer::Type targetType = _getRandomType();
    level->randomizeDancerTypes(generateTypeVector(targetType));
    level->setTarget(_rng.getNextNumber(0, level->getDancers().size()-1));
    level->setTargetType(targetType);

    return std::move(level);
}

std::unique_ptr<Level> Levels::makeCircle(int difficulty)
{
    auto level = std::make_unique<Level>();

    int numberOfDancers = 8 + 2*difficulty;
    if (numberOfDancers > 48)
    {
        numberOfDancers = 48;
    }

    bool reverse = static_cast<bool>(_rng.getNextNumber(0,1));

    for (int i = 0; i < numberOfDancers; i++)
    {
        double angle = i*(M_PI*2/numberOfDancers);
        level->addDancer(Dancer(&DancePatterns::circle, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(0.8*(reverse?-1:1), 0.8), angle, 1.0));
    }

    Dancer::Type targetType = _getRandomType();
    level->randomizeDancerTypes(generateTypeVector(targetType));
    level->setTarget(_rng.getNextNumber(0, level->getDancers().size()-1));
    level->setTargetType(targetType);

    return std::move(level);
}

std::unique_ptr<Level> Levels::makeFlower(int difficulty)
{
    auto level = std::make_unique<Level>();

    int numberOfDancers = 8 + 2*difficulty;
    if (numberOfDancers > 48)
    {
        numberOfDancers = 48;
    }

    bool reverse = static_cast<bool>(_rng.getNextNumber(0,1));

    for (int i = 0; i < numberOfDancers; i++)
    {
        double angle = i*(M_PI*2/numberOfDancers);
        level->addDancer(Dancer(&DancePatterns::flower, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(0.8*(reverse?-1:1), 0.8), angle, 0.1));
    }

    Dancer::Type targetType = _getRandomType();
    level->randomizeDancerTypes(generateTypeVector(targetType));
    level->setTarget(_rng.getNextNumber(0, level->getDancers().size()-1));
    level->setTargetType(targetType);

    return std::move(level);
}

std::unique_ptr<Level> Levels::makeKikibouba(int difficulty)
{
    auto level = std::make_unique<Level>();

    int numberOfDancers = 8 + 2*difficulty;
    if (numberOfDancers > 48)
    {
        numberOfDancers = 48;
    }

    bool reverse = static_cast<bool>(_rng.getNextNumber(0,1));

    for (int i = 0; i < numberOfDancers; i++)
    {
        double angle = i*(M_PI*2/numberOfDancers);
        level->addDancer(Dancer(&DancePatterns::kikibouba, LeoEngine::Pair<double, double>(0.0, 0.0), LeoEngine::Pair<double, double>(0.7*(reverse?-1:1), 0.7), angle, 0.6));
    }

    Dancer::Type targetType = _getRandomType();
    level->randomizeDancerTypes(generateTypeVector(targetType));
    level->setTarget(_rng.getNextNumber(0, level->getDancers().size()-1));
    level->setTargetType(targetType);

    return std::move(level);
}

