#ifndef GALENACPP_VARMANAGER_CLASS
#define GALENACPP_VARMANAGER_CLASS

#include <iostream>
#include <iomanip>

#include <map>
#include <string>

#include "./Memory.h"
#include "./Binary.h"

using namespace std;
using namespace Binary;

enum type
{
    DOUBLE,
    INT
};

typedef struct linker
{
    int addr;
    type var_type;
} linker;

class VarManager
{
public:
    VarManager(bool expandable = true, int size = 0);

    bool is_set(string name);
    int size_of(type var_type);
    int size_of(linker l);
    int size_of(string name);

    int set_double(string name, double value);
    // int set_int(string name, int value);

    double get_double(string name);
    // int get_int(string name);

    void unset(string name);

    Memory &get_mem();

    friend ostream &operator<<(ostream &os, VarManager &vm);

private:
    Memory memory;
    map<string, linker> linkers;
};

#endif // !GALENACPP_VARMANAGER_CLASS