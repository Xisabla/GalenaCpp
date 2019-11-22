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
    case JNZ: return "JNZ";
    case JMP: return "JMP";
    case CMPEQU: return "CMPEQU";
    case CMPGTR: return "CMPGTR";
    case CMPGTE: return "CMPGTE";
    case CMPLSS: return "CMPLSS";
    case CMPLSE: return "CMPLSE";
    case CMPNOT: return "CMPNOT";
    case CMPOR: return " OR ";
    case CMPAND: return "AND";
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
    if (name == "JNZ") return JNZ;
    if (name == "JMP") return JMP;
    if (name == "GET") return GET;
    if (name == "CMPEQU") return CMPEQU;
    if (name == "CMPGTR") return CMPGTR;
    if (name == "CMPGTE") return CMPGTE;
    if (name == "CMPLSS") return CMPLSS;
    if (name == "CMPLSE") return CMPLSE;
    if (name == "CMPNOT") return CMPNOT;
    if (name == "CMPOR") return CMPOR;
    if (name == "CMPAND") return CMPAND;

    return NONE;
}