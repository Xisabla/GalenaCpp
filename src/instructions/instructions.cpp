#include "instructions.h"

string Instructions::name(Instruction ins)
{
    switch (ins)
    {
    case ADD: return "ADD";
    case SUB: return "SUB";
    case DIV: return "DIV";
    case MUL: return "MUL";
    case NUM: return "NUM";
    case OUT: return "OUT";
    case INP: return "INP";
    case SET: return "SET";
    case GET: return "GET";
    case NONE: return "NONE";
    default: return to_string(ins);
    }
}

Instructions::Instruction Instructions::get_ins(string name)
{
    if (name == "ADD") return ADD;
    if (name == "SUB") return SUB;
    if (name == "DIV") return DIV;
    if (name == "MUL") return MUL;
    if (name == "NUM") return NUM;
    if (name == "OUT") return OUT;
    if (name == "INP") return INP;
    if (name == "SET") return SET;
    if (name == "GET") return GET;

    return NONE;
}