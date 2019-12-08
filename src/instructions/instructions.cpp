#include "instructions.h"

string Instructions::name(Instruction ins)
{
    switch (ins)
    {
    case ADD: return "ADD";
    case SUB: return "SUB";
    case DIV: return "DIV";
    case MUL: return "MUL";
    case POW: return "POW";
    case INC: return "INC";
    case DEC: return "DEC";
    case NUM: return "NUM";
    case OUT: return "OUT";
    case OUL: return "OUL";
    case INP: return "INP";
    case SET: return "SET";
    case GET: return "GET";
    case JNZ: return "JNZ";
    case JMP: return "JMP";
    case CLL: return "CLL";
    case RTR: return "RTR";
    case PLT: return "PLT";
    case CEQ: return "CEQ";
    case CGR: return "CGR";
    case CGE: return "CGE";
    case CLS: return "CLS";
    case CLE: return "CLE";
    case CNT: return "CNT";
    case COR: return "COR";
    case CND: return "CND";
    case RNT: return "RNT";
    case RCP: return "RCP";
    case RIC: return "RIP";
    case NOP: return "NOP";
    default: return to_string(ins);
    }
}

Instructions::Instruction Instructions::get_ins(string name)
{
    if (name == "ADD") return ADD;
    if (name == "SUB") return SUB;
    if (name == "DIV") return DIV;
    if (name == "MUL") return MUL;
    if (name == "POW") return POW;
    if (name == "INC") return INC;
    if (name == "DEC") return DEC;
    if (name == "NUM") return NUM;
    if (name == "OUT") return OUT;
    if (name == "OUL") return OUL;
    if (name == "INP") return INP;
    if (name == "SET") return SET;
    if (name == "GET") return GET;
    if (name == "JNZ") return JNZ;
    if (name == "JMP") return JMP;
    if (name == "CLL") return CLL;
    if (name == "RTR") return RTR;
    if (name == "PLT") return PLT;
    if (name == "CEQ") return CEQ;
    if (name == "CGR") return CGR;
    if (name == "CGE") return CGE;
    if (name == "CLS") return CLS;
    if (name == "CLE") return CLE;
    if (name == "CNT") return CNT;
    if (name == "COR") return COR;
    if (name == "CND") return CND;
    if (name == "RNT") return RNT;
    if (name == "RCP") return RCP;
    if (name == "RIC") return RIC;
    return NOP;
}