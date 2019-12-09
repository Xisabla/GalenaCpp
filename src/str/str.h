#ifndef GALENACPP_STR
#define GALENACPP_STR

#include "stdlib.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

char *trim(char *str, char c);

vector<string> split(string &s, char delimiter);

#endif // !GALENACPP_STR