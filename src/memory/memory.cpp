#include "./memory.h"

//
// ─── CONSTRUCTOR ────────────────────────────────────────────────────────────────
//

Memory::Memory() : variables(), v_double(){};

//
// ─── GLOBAL ─────────────────────────────────────────────────────────────────────
//

bool Memory::is_set(string name)
{
    return variables.find(name) != variables.end();
}

var_type Memory::get_type(string name)
{
    return is_set(name) ? variables[name] : UNDEFINED;
}

void Memory::unset(string name)
{
    if (is_set(name))
    {
        switch (variables[name])
        {
        case DOUBLE: v_double.erase(name); break;
        default: break;
        }

        variables.erase(name);
    }
}

//
// ─── SETTER ─────────────────────────────────────────────────────────────────────
//

double Memory::get_double(string name)
{
    return v_double.find(name) == v_double.end() ? 0 : v_double[name];
}

//
// ─── GETTER ─────────────────────────────────────────────────────────────────────
//

void Memory::set_double(string name, double value)
{
    variables[name] = DOUBLE;
    v_double[name]  = value;
}