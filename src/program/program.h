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

typedef struct options
{
    bool debug;
} options;

class Program
{
public:
    Program();
    Program(map<string, bool> opt);

    int ins(Instruction instr, double data);

    bool read(string filename);
    bool read(ifstream &is);
    bool write(string filename);
    bool write(ofstream &fs);

    void run();

    int exec_add(int current_ins, double data);
    int exec_sub(int current_ins, double data);
    int exec_div(int current_ins, double data);
    int exec_mul(int current_ins, double data);
    int exec_num(int current_ins, double data);
    int exec_out(int current_ins, double data);

    bool get_opt(string name);
    void set_opt(string name, bool value);

    friend ostream &operator<<(ostream &os, Program &prog);

private:
    int nb_instr;
    vector<pair<Instruction, double>> instructions;
    vector<double> pile;
    map<string, bool> opt;

    double pop();
    void push(double data);
};

#endif // !GALENACPP_PROGRAM