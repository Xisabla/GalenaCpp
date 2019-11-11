#ifndef GALENACPP_MEMORY
#define GALENACPP_MEMORY

#include <iomanip>
#include <iostream>

#include <map>
#include <string>

using namespace std;

enum var_type
{
    UNDEFINED = -1,
    DOUBLE
};

class Memory
{
public:
    // Constructor
    Memory();

    // Global
    bool is_set(string name);
    var_type get_type(string name);
    void unset(string name);

    // Setters
    double get_double(string name);

    // Getters
    void set_double(string name, double value);

    friend ostream &operator<<(ostream &os, Memory &memory);

private:
    map<string, var_type> variables;
    map<string, double> v_double;
};

#endif // !GALENACPP_MEMORY