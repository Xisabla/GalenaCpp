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
    POW,
    INC,
    DEC,
    NUM,
    OUT,
    OUL,
    INP,
    SET,
    GET,
    JMP,
    JNZ,
    CLL,
    RTR,
    PLT,
    CEQ,
    CGR,
    CGE,
    CLS,
    CLE,
    CNT,
    COR,
    CND,
    RNT,
    RCP,
    RIC,
    NOP
};

string name(Instruction ins);
Instruction get_ins(string name);

} // namespace Instructions

#endif // !GALENACPP_INSTRUCTIONS