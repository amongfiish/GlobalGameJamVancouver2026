#include <cmath>
#include "DancePatterns.hpp"

DancePatterns::DancePattern DancePatterns::still = [](double t){ return LeoEngine::Pair<double, double>(0, 0); };
DancePatterns::DancePattern DancePatterns::linear = [](double t){ return LeoEngine::Pair<double, double>(t, t); };
DancePatterns::DancePattern DancePatterns::circle = [](double t){ return LeoEngine::Pair<double, double>(cos(t), sin(t)); };
DancePatterns::DancePattern DancePatterns::flower = [](double t){ return LeoEngine::Pair<double, double>(cos(10*t)*cos(t), cos(10*t)*sin(t)); };
DancePatterns::DancePattern DancePatterns::kikibouba = [](double t){ return LeoEngine::Pair<double, double>((1+0.2*cos(10*t))*cos(t), (1+0.2*cos(10*t))*sin(t)); };

