#ifndef GALENACPP_INSTRUCTIONS
#define GALENACPP_INSTRUCTIONS

#include <string>

using namespace std;

namespace Instructions
{

enum Instruction
{
    ADD,
    SUB,
    DIV,
    MUL,
    INC,
    DEC,
    NUM,
    OUT,
    OUTL,
    INP,
    SET,
    GET,
    JMP,
    JNZ,
    CMPEQU,
    CMPGTR,
    CMPGTE,
    CMPLSS,
    CMPLSE,
    CMPNOT,
    CMPOR,
    CMPAND,
    FORINIT,
    FORTEST,
    FORINCR,
    NONE
};

string name(Instruction ins);
Instruction get_ins(string name);

} // namespace Instructions

#endif // !GALENACPP_INSTRUCTIONS