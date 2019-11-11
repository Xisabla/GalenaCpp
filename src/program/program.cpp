#include "./program.h"

//
// ──────────────────────────────────────────────────────────────────── I ──────────
//   :::::: P U B L I C   M E T H O D S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────
//

//
// ─── CONSTRUCTORS ───────────────────────────────────────────────────────────────
//

Program::Program() : instructions(), nb_instr(0), pile(), opt({{"welcome", true}}){};

Program::Program(map<string, bool> opt) : instructions(), nb_instr(0), pile(), opt({{"welcome", true}}){};

//
// ─── INSTRUCTIONS ───────────────────────────────────────────────────────────────
//

/**
 *  Insert an instruction into the instruction vector
 * 
 *  @param ins The instruction to insert
 *  @param data The specific data related to the instruction
 *  @returns The instruction id inside the vector
 *  
 *  @example Program prog; prog.ins(ADD, 0);
 *  @example Program prog; prog.ins(NUMBER, -15);
 *
 *  NOTE: For documentation, specify each instruction, and its data
 */
int Program::ins(Instruction ins, double data)
{
    instructions.push_back(make_pair(ins, data));

    return this->nb_instr++;
}

// ────────────────────────────────────────────────────────────────────────────────

//
// ─── I/O FILES ──────────────────────────────────────────────────────────────────
//

/**
 *  Read the instruction vector into a file from its filename
 * 
 *  @param filename The path to file or the filename (with extension) in context directory
 *  @returns True if the file can be read, False otherwise
 */
bool Program::read(string filename)
{
    ifstream file(filename);

    return read(file);
}

/**
 *  Read the instruction vector into a file from an input file stream
 *  
 *  @param is The input file stream to read
 *  @returns True if the file stream can be read, False otherwise
 * 
 *  @example ifstream file("input.exec"); prog.read(file);
 */
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

/**
 *  Write the instruction vector from a file from its filename
 * 
 *  @param filename The path to file or the filename (with extension) in context directory
 *  @returns True if the file can be read, False otherwise
 */
bool Program::write(string filename) const
{
    ofstream file(filename);

    return write(file);
}

/**
 *  Write the instruction vector into from file from an input file stream
 *  
 *  @param is The input file stream to read
 *  @returns True if the file stream can be read, False otherwise
 * 
 *  @example ofstream file("output.exec"); prog.write("output.exec");
 */
bool Program::write(ofstream &fs) const
{
    if (!fs.is_open())
        return false;

    int i = 0;

    for (auto &ins : instructions)
        fs << i++ << '\t' << name(ins.first) << '\t' << ins.second << endl;

    return false;
}

//
// ─── RUNNER ─────────────────────────────────────────────────────────────────────
//

/**
 *  Run the program
 * 
 *  Read each instruction from the instruction vector, and run
 *      the relative executor of each instructions
 * 
 *  If the instruction does not have any executor, go to the
 *      next instruction
 * 
 *  @todo Put each instruction and its relative executor inside a map
 */
void Program::run()
{
    if (get_opt("write")) write("output.exec");

    cout << "================ EXECUTION ===============" << endl;

    int current_ins = 0;

    while (current_ins < instructions.size())
    {
        Instruction ins = instructions[current_ins].first;
        double data     = instructions[current_ins].second;

        // TODO: Build a map of executor methods

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

//
// ─── EXECUTORS ──────────────────────────────────────────────────────────────────
//

/**
 *  Execute "ADD" instruction
 * 
 *  Pop out the two numbers to add from the pile, and then push the sum
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_add(int &current_ins, double data)
{
    double x = pop();
    double y = pop();

    push(y + x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " + " << x << " = " << y + x << endl;

    return ++current_ins;
}

/**
 *  Execute "SUB" instruction
 * 
 *  Pop out the two numbers to add from the pile, and then push the difference
 * 
 *  NOTE: Let x - y the difference; as x has been pushed before y, y will
 *      popped first. Then for x' and y' the first and the second number
 *      to be popped from the pile: x' = y; y' = x so x - y = y' - x'
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_sub(int &current_ins, double data)
{
    double x = pop();
    double y = pop();

    push(y - x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " - " << x << " = " << y - x << endl;

    return ++current_ins;
}

/**
 *  Execute "DIV" instruction
 * 
 *  Pop out the two numbers to divide from the pile, and then push the division 
 * 
 *  NOTE: Let x / y the difference; as x has been pushed before y, y will
 *      popped first. Then for x' and y' the first and the second number
 *      to be popped from the pile: x' = y; y' = x so x / y = y' / x'
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_div(int &current_ins, double data)
{
    double x = pop();
    double y = pop();

    push(y / x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " / " << x << " = " << y / x << endl;

    return ++current_ins;
}

/**
 *  Execute "MUL" instruction
 * 
 *  Pop out the two numbers to multiply from the pile, and then push the multiplication
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_mul(int &current_ins, double data)
{
    double x = pop();
    double y = pop();

    push(y * x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " * " << x << " = " << y * x << endl;

    return ++current_ins;
}

/**
 *  Execute "NUM" instruction
 * 
 *  Push a number into the pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data The number to push to the pile
 *  @returns The next instruction id
 */
int Program::exec_num(int &current_ins, double data)
{
    push(data);

    if (get_opt("debug"))
        cout << "(debug) push: " << data << endl;

    return ++current_ins;
}

/**
 *  Execute "OUT" instruction
 * 
 *  Pop out and show the first element of the pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 * 
 *  NOTE: Data param can be used to set the precision, or some specific options
 */
int Program::exec_out(int &current_ins, double data)
{
    cout << pop() << endl;

    return ++current_ins;
}

//
// ─── OPTIONS ────────────────────────────────────────────────────────────────────
//

/**
 *  Fetch the value (true/false) of an option defined before (default: false)
 * 
 *  @param name The name of the option to get
 *  @returns The boolean value of the option if it exists, False otherwise
 */
bool Program::get_opt(string name)
{
    if (opt.find(name) != opt.end())
        return opt[name];

    return false;
}

/**
 *  Set the value of an option
 * 
 *  @param name The name of the option to set
 *  @param value The boolean value of the option (default: true)
 * 
 *  @example prog.set_opt("debug", true);
 *  @example prog.set_opt("debug")
 */
void Program::set_opt(string name, bool value)
{
    opt[name] = value;
}

//
// ─── PRINT ──────────────────────────────────────────────────────────────────────
//

/**
 *  Write the program instructions (and the beautiful logo) into an output stream
 *      through the operator "<<"
 * 
 *  @param os The output stream in which the instructions will be written
 *  @param prog The Program object to show
 *  @returns The output stream
 * 
 *  @example cout << prog << endl;
 */
ostream &operator<<(ostream &os, Program &prog)
{
    if (prog.get_opt("welcome"))
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
    }

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

//
// ─────────────────────────────────────────────────────────── PUBLIC METHODS ─────
//

//
// ────────────────────────────────────────────────────────────────────── II ──────────
//   :::::: P R I V A T E   M E T H O D S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────

//
// ─── PILE ───────────────────────────────────────────────────────────────────────
//

/**
 *  Pop out the first value of the pile
 * 
 *  @returns The first value of the pile
 */
double Program::pop()
{
    if (pile.size() == 0)
        return 0;

    double val = pile[pile.size() - 1];

    pile.pop_back();

    return val;
}

/**
 *  Push a value on top of the pile
 * 
 *  @param data The value to push in the pile
 */
void Program::push(double data)
{
    pile.push_back(data);
}

//
// ────────────────────────────────────────────────────────── PRIVATE METHODS ─────
//