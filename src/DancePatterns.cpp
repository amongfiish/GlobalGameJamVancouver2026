#include "DancePatterns.hpp"

DancePatterns::DancePattern DancePatterns::still = [](double t){ return LeoEngine::Pair<double, double>(0, 0); };
DancePatterns::DancePattern DancePatterns::linear = [](double t){ return LeoEngine::Pair<double, double>(t, t); };
DancePatterns::DancePattern DancePatterns::circle = [](double t){ return LeoEngine::Pair<double, double>(cos(t), sin(t)); };

