#include "./program.h"

Program::Program() : instructions(), nb_instr(0), tokens(), pile(){};
Program::Program(map<int, string> tokens) : instructions(), nb_instr(0), tokens(tokens), pile(){};

int Program::ins(int ins, double data)
{
    instructions.push_back(make_pair(ins, data));

    return this->nb_instr++;
}

void Program::set_token(int token, string value)
{
    this->tokens[token] = value;
}

void Program::set_tokens(map<int, string> tokens)
{
    this->tokens = tokens;
}

int Program::get_token(string name)
{
    for (auto &t : this->tokens)
        if (t.second == name)
            return t.first;

    return -1;
}

map<string, int> Program::get_tokens()
{
    map<string, int> tokens;

    for (auto &t : this->tokens)
        tokens[t.second] = t.first;

    return tokens;
}

string Program::get_token_name(int token)
{
    if (tokens.find(token) != tokens.end())
        return tokens[token];

    return to_string(token);
}

map<int, string> Program::get_token_names()
{
    return tokens;
}

bool Program::token_is(int ins, string name)
{
    return ins == get_token(name);
}

void Program::write(string filename)
{
    ofstream file(filename);

    write(file);
}

void Program::write(ofstream &fs)
{
    int i = 0;

    for (auto &ins : instructions)
        fs << i++ << '\t' << get_token_name(ins.first) << '\t' << ins.second << endl;
}

void Program::run()
{

    cout << "================ EXECUTION ===============" << endl;

    int current_ins = 0;

    while (current_ins < instructions.size())
    {
        auto ins = instructions[current_ins];
        int token = ins.first;

        // TODO: if (token_is(token, "ADD")) prog.exec_add()
        if (token_is(token, "ADD"))
        {
            double x = pop();
            double y = pop();
            pile.push_back(x + y);

            cout << "(debug) " << x << " + " << y << " = " << x + y << endl;
            current_ins++;
        }
        else if (token_is(token, "NUM"))
        {
            pile.push_back(ins.second);
            current_ins++;
        }
        else
        {
            current_ins++;
        }
    }

    cout << "==========================================" << endl;
}

ostream &operator<<(ostream &os, Program &prog)
{

    os << "┌────────────────────────────────────────┐" << endl;
    os << "│                                        │" << endl;
    os << "│               GalenaC++                │" << endl;
    os << "│                                        │" << endl;
    os << "├────────────────────────────────────────┤" << endl;
    os << "│                                        │" << endl;
    os << "│                    \\\\                  │" << endl;
    os << "│                    (o>                 │" << endl;
    os << "│                \\\\_//)                  │" << endl;
    os << "│                 \\_/_)                  │" << endl;
    os << "│                  _|_                   │" << endl;
    os << "│                       v1.0.0           │" << endl;
    os << "├────────────────────────────────────────┤" << endl;
    os << "│ © Copyright 2019 - ARBACHE - MIQUET    │" << endl;
    os << "└────────────────────────────────────────┘" << endl
       << endl;

    os << "┌────────────────────────────────────────┐" << endl;
    os << "│     i  INS             data            │" << endl;
    os << "├────────────────────────────────────────┤" << endl;

    int i = 0;

    for (auto &ins : prog.instructions)
    {
        os << "│ " << setw(5) << i++ << setw(5);

        if (prog.tokens.find(ins.first) != prog.tokens.end())
            os << prog.tokens[ins.first];
        else
            os << to_string(ins.first);

        os << setw(28) << ins.second << " │" << endl;
    }

    os << "├────────────────────────────────────────┤" << endl;
    os << "│    Total: "
       << setw(5) << prog.instructions.size()
       << " instructions           │" << endl;
    os << "└────────────────────────────────────────┘" << endl;

    return os;
}

double Program::pop()
{
    if (pile.size() == 0)
        return 0;

    double val = pile[pile.size() - 1];

    pile.pop_back();

    return val;
}