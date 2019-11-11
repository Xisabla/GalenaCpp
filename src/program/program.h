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
    // Constructors
    Program();
    Program(map<string, bool> opt);

    // Instructions
    int ins(Instruction instr, double data);

    // I/O Files
    bool read(string filename);
    bool read(ifstream &is);
    bool write(string filename) const;
    bool write(ofstream &fs) const;

    // Runner
    void run();

    // Executors
    int exec_add(int &current_ins, double data = 0);
    int exec_sub(int &current_ins, double data = 0);
    int exec_div(int &current_ins, double data = 0);
    int exec_mul(int &current_ins, double data = 0);
    int exec_num(int &current_ins, double data);
    int exec_out(int &current_ins, double data = 0);

    // Options
    bool get_opt(string name);
    void set_opt(string name, bool value = true);

    // Debug
    friend ostream &operator<<(ostream &os, Program &prog);

private:
    // Members
    int nb_instr;                                   // number of instructions
    vector<pair<Instruction, double>> instructions; // vector of instructions
    vector<double> pile;                            // data pile
    map<string, bool> opt;                          // options map

    // Pile
    double pop();
    void push(double data);
};

#endif // !GALENACPP_PROGRAM