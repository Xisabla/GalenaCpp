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
    NUM,
    OUT,
    INP,
    SET,
    GET,
    NONE
};

string name(Instruction ins);
Instruction get_ins(string name);

} // namespace Instructions

#endif // !GALENACPP_INSTRUCTIONS