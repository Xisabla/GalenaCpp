#ifndef GALENACPP_PROGRAM
#define GALENACPP_PROGRAM

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "../instructions/instructions.h"
#include "../memory/memory.h"

using namespace Instructions;
using namespace std;

typedef struct targeter
{
    int ic_goto;
    int ic_false;
} t_targeter;

class Program
{
public:
    // Constructors
    Program();
    Program(map<string, bool> opt);

    // Instructions
    int ic();
    int ins(Instruction instr, double data);
    int ins(Instruction instr, string data);
    string &operator[](int idx);

    // Routines
    void set_routine(string name, int index, int nb_args);

    // I/O Files
    bool read(string filename);
    bool read(ifstream &is);
    bool write(string filename) const;
    bool write(ofstream &fs) const;

    // Runner
    void run();

    // Executors
    int exec_add(int &current_ins, string data);
    int exec_sub(int &current_ins, string data);
    int exec_div(int &current_ins, string data);
    int exec_mul(int &current_ins, string data);
    int exec_inc(int &current_ins, string data);
    int exec_dec(int &current_ins, string data);
    int exec_num(int &current_ins, string data);
    int exec_out(int &current_ins, string data);
    int exec_oul(int &current_ins, string data);
    int exec_inp(int &current_ins, string data);
    int exec_set(int &current_ins, string data);
    int exec_get(int &current_ins, string data);
    int exec_jnz(int &current_ins, string data);
    int exec_jmp(int &current_ins, string data);
    int exec_cll(int &current_ins, string data);
    int exec_rtr(int &current_ins, string data);
    int exec_ceq(int &current_ins, string data);
    int exec_cgr(int &current_ins, string data);
    int exec_cge(int &current_ins, string data);
    int exec_cls(int &current_ins, string data);
    int exec_cle(int &current_ins, string data);
    int exec_cnt(int &current_ins, string data);
    int exec_cor(int &current_ins, string data);
    int exec_cnd(int &current_ins, string data);
    int exec_rnt(int &current_ins, string data);
    int exec_rcp(int &current_ins, string data);
    int exec_ric(int &current_ins, string data);

    // Options
    bool get_opt(string name);
    void set_opt(string name, bool value = true);

    // Print
    friend ostream &operator<<(ostream &os, Program &prog);

private:
    // Members
    int nb_instr;                                   // number of instructions
    vector<pair<Instruction, string>> instructions; // vector of instructions
    vector<string> pile;                            // data pile
    vector<pair<int, int>> f_pile;                  // for iterators pile
    vector<int> c_pile;                             // call stack
    map<string, bool> opt;                          // options map
    map<string, pair<int, int>> routines;           // routines map, containing index and arg count
    Memory memory;                                  // memory

    // Pile
    string pop();
    void push(string data);
    double pop_d();
    void push(double data);

    // For pile
    void f_push(int i, int n);
    pair<int, int> f_pop();

    // Call Stack
    int pop_c();
};

#endif // !GALENACPP_PROGRAM