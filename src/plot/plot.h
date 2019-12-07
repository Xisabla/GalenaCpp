#ifndef GALENACPP_PLOT
#define GALENACPP_PLOT

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;

bool plot_points(vector<pair<double, double>> points, bool lines = true, bool loop = false);

bool plot(vector<pair<double, double>> points, int offset = 50, int width = 1300, int height = 700);

#endif // !GALENACPP_PLOT