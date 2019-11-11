#ifndef GALENACPP_PROGRAM
#define GALENACPP_PROGRAM

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <string>
#include <map>
#include <vector>

#include "../instructions/instructions.h"

using namespace Instructions;
using namespace std;

class Program
{
public:
    Program();

    int ins(Instruction instr, double data);

    bool read(string filename);
    bool read(ifstream &is);
    bool write(string filename);
    bool write(ofstream &fs);

    void run();

    friend ostream &operator<<(ostream &os, Program &prog);

private:
    int nb_instr;
    vector<pair<Instruction, double>> instructions;
    vector<double> pile;

    double pop();
};

#endif // !GALENACPP_PROGRAM