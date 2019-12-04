#ifndef GALENACPP_PLOT
#define GALENACPP_PLOT

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;

bool plot_points(vector<pair<double, double>> points, bool lines = true, bool loop = false);

#endif // !GALENACPP_PLOT