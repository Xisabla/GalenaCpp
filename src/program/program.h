#ifndef GALENACPP_PROGRAM
#define GALENACPP_PROGRAM

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <map>
#include <vector>

using namespace std;

class Program
{
public:
    Program();
    Program(map<int, string> tokens);

    int ins(int instr, double data);

    void set_token(int token, string value);
    void set_tokens(map<int, string> tokens);

    int get_token(string name);
    map<string, int> get_tokens();

    string get_token_name(int token);
    map<int, string> get_token_names();

    bool token_is(int ins, string name);

    void write(string filename);
    void write(ofstream &fs);

    void run();

    friend ostream &operator<<(ostream &os, Program &prog);

private:
    int nb_instr;
    map<int, string> tokens;
    vector<pair<int, double>> instructions;
    vector<double> pile;

    double pop();
};

#endif