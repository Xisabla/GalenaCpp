#include "./program.h"

Program::Program() : instructions(), nb_instr(0), pile(){};
Program::Program(map<string, bool> opt) : instructions(), nb_instr(0), pile(), opt(opt){};

int Program::ins(Instruction ins, double data)
{
    instructions.push_back(make_pair(ins, data));

    return this->nb_instr++;
}

bool Program::read(string filename)
{
    ifstream file(filename);

    return read(file);
}

bool Program::read(ifstream &is)
{
    if (!is.is_open())
        return false;

    string line;

    while (getline(is, line))
    {
        int i;
        string ins_name;
        double data;

        istringstream iss(line);
        if (!(iss >> i >> ins_name >> data))
            break;

        instructions.push_back(make_pair(get_ins(ins_name), data));
    }

    return true;
}

bool Program::write(string filename)
{
    ofstream file(filename);

    return write(file);
}

bool Program::write(ofstream &fs)
{
    if (!fs.is_open())
        return false;

    int i = 0;

    for (auto &ins : instructions)
        fs << i++ << '\t' << name(ins.first) << '\t' << ins.second << endl;

    return false;
}

void Program::run()
{

    cout << "================ EXECUTION ===============" << endl;

    int current_ins = 0;

    while (current_ins < instructions.size())
    {
        Instruction ins = instructions[current_ins].first;
        double data = instructions[current_ins].second;

        // TODO: Put instructions execution as private (public ?) methods
        //      --> if(ins == SOMETHING) prog.exec_something(data);
        // Then, give "current_ins" as a reference or make it as class member
        //  to be edited by the "exec_something" method

        // NOTE: Maybe create and give a context object (whatever it is, it may be useful)
        //      --> prog.exec_something(data, context)
        //      Useful things:
        //          - bool: debug

        if (ins == ADD)
            current_ins = exec_add(current_ins, data);
        else if (ins == SUB)
            current_ins = exec_sub(current_ins, data);
        else if (ins == DIV)
            current_ins = exec_div(current_ins, data);
        else if (ins == MUL)
            current_ins = exec_mul(current_ins, data);
        else if (ins == NUM)
            current_ins = exec_num(current_ins, data);
        else if (ins == OUT)
            current_ins = exec_out(current_ins, data);
        else
            current_ins++;
    }

    cout << "==========================================" << endl;
}

int Program::exec_add(int current_ins, double data)
{
    double x = pop();
    double y = pop();

    push(y + x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " + " << x << " = " << y + x << endl;

    return ++current_ins;
}

int Program::exec_sub(int current_ins, double data)
{
    double x = pop();
    double y = pop();

    push(y - x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " - " << x << " = " << y - x << endl;

    return ++current_ins;
}

int Program::exec_div(int current_ins, double data)
{
    double x = pop();
    double y = pop();

    push(y / x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " / " << x << " = " << y / x << endl;

    return ++current_ins;
}

int Program::exec_mul(int current_ins, double data)
{
    double x = pop();
    double y = pop();

    push(y * x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " * " << x << " = " << y * x << endl;

    return ++current_ins;
}

int Program::exec_num(int current_ins, double data)
{
    push(data);

    if (get_opt("debug"))
        cout << "(debug) push: " << data << endl;

    return ++current_ins;
}

int Program::exec_out(int current_ins, double data)
{
    cout << pop() << endl;

    return ++current_ins;
}

bool Program::get_opt(string name)
{
    if (opt.find(name) != opt.end())
        return opt[name];

    return false;
}

void Program::set_opt(string name, bool value)
{
    opt[name] = value;
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
        os << "│ " << setw(5) << i++ << setw(5) << name(ins.first) << setw(28) << ins.second << " │" << endl;
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

void Program::push(double data)
{
    pile.push_back(data);
}