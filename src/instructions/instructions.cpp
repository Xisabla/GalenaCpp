#include "instructions.h"

string Instructions::name(Instruction ins)
{
    switch (ins)
    {
    case ADD:
        return "ADD";
    case SUB:
        return "SUB";
    case DIV:
        return "DIV";
    case MUL:
        return "MUL";
    case NUM:
        return "NUM";
    case NONE:
        return "NONE";
    default:
        return to_string(ins);
    }
}

Instructions::Instruction Instructions::get_ins(string name)
{
    if (name == "ADD")
        return ADD;
    if (name == "SUB")
        return SUB;
    if (name == "DIV")
        return DIV;
    if (name == "MUL")
        return MUL;
    if (name == "NUM")
        return NUM;
    return NONE;
}