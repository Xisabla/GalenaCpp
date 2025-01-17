#include "./program.h"

//
// ──────────────────────────────────────────────────────────────────── I ──────────
//   :::::: P U B L I C   M E T H O D S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────
//

//
// ─── CONSTRUCTORS ───────────────────────────────────────────────────────────────
//

Program::Program() : instructions(), nb_instr(0), pile(), f_pile(), c_pile(), routines(), opt({{"bienvenue", true}}), memory(){};

Program::Program(map<string, bool> opt) : instructions(), nb_instr(0), pile(), f_pile(), c_pile(), routines(), opt({{"bienvenue", true}}), memory(){};

//
// ─── INSTRUCTIONS ───────────────────────────────────────────────────────────────
//

int Program::ic()
{
    return nb_instr;
}

/**
 *  Insert an instruction as a double into the instruction vector
 * 
 *  @param ins The instruction to insert
 *  @param data The specific data string related to the instruction
 *  @returns The instruction id inside the vector
 */
int Program::ins(Instruction ins, double data)
{
    return this->ins(ins, to_string(data));
}

/**
 *  Insert an instruction into the instruction vector
 * 
 *  @param ins The instruction to insert
 *  @param data The specific data string related to the instruction
 *  @returns The instruction id inside the vector
 *  
 *  @example Program prog; prog.ins(ADD, 0);
 *  @example Program prog; prog.ins(NUMBER, -15);
 *
 *  NOTE: For documentation, specify each instruction, and its data
 */
int Program::ins(Instruction ins, string data)
{
    instructions.push_back(make_pair(ins, data));

    return this->nb_instr++;
}

/**
 *  Get the instruction data for a given instruction id
 *  Allow edition
 * 
 *  @param idx The id of the instruction in the instruction vector
 *  @returns The instruction data string as reference
 * 
 *  @example string data = prog[12]
 *  @example prog[32] = "value"
 *  
 */
string &Program::operator[](int idx)
{
    return instructions[idx].second;
}

// ────────────────────────────────────────────────────────────────────────────────

//
// ─── ROUTINES ───────────────────────────────────────────────────────────────────
//

void Program::set_routine(string name, int index, int nb_args) {
    routines[name] = make_pair(index, nb_args);
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
        string data;

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
        fs << i++ << '\t' << setw(13) << name(ins.first) << "\t\t" << ins.second << endl;

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
 */
void Program::run()
{
    if (get_opt("ecrire")) write("output.exec");
    if (get_opt("voir_exec")) cout << *this << endl;

    cout << "================ EXECUTION ===============" << endl;

    int current_ins = 0;

    while (current_ins < instructions.size())
    {
        Instruction ins = instructions[current_ins].first;
        string data     = instructions[current_ins].second;
        current_ins = exec(ins, current_ins, data);
    }
    cout << "==========================================" << endl;
}

/**
 *  Run an instruction
 * 
 *  Fin the executor for the given instruction, run it and return
 *  the next instruction id
 * 
 *  @param ins The instruction to execute
 *  @param current_ins The instruction id
 *  @param data The data to give to the instruction
 * 
 *  @returns The next instruction id
 */
int Program::exec(Instruction ins, int& current_ins, string data)
{
    if (ins == ADD)
        current_ins = exec_add(current_ins, data);
    else if (ins == SUB)
        current_ins = exec_sub(current_ins, data);
    else if (ins == DIV)
        current_ins = exec_div(current_ins, data);
    else if (ins == MUL)
        current_ins = exec_mul(current_ins, data);
    else if (ins == POW)
        current_ins = exec_pow(current_ins, data);
    else if (ins == INC)
        current_ins = exec_inc(current_ins, data);
    else if (ins == DEC)
        current_ins = exec_dec(current_ins, data);
    else if (ins == NUM)
        current_ins = exec_num(current_ins, data);
    else if (ins == OUT)
        current_ins = exec_out(current_ins, data);
    else if (ins == OUL)
        current_ins = exec_oul(current_ins, data);
    else if (ins == INP)
        current_ins = exec_inp(current_ins, data);
    else if (ins == SET)
        current_ins = exec_set(current_ins, data);
    else if (ins == GET)
        current_ins = exec_get(current_ins, data);
    else if (ins == JNZ)
        current_ins = exec_jnz(current_ins, data);
    else if (ins == JMP)
        current_ins = exec_jmp(current_ins, data);
    else if(ins == CLL) 
        current_ins = exec_cll(current_ins, data);
    else if(ins == RTR) 
        current_ins = exec_rtr(current_ins, data);
    else if(ins == PLT) 
        current_ins = exec_plt(current_ins, data);
    else if (ins == CEQ)
        current_ins = exec_ceq(current_ins, data);
    else if (ins == CGR)
        current_ins = exec_cgr(current_ins, data);
    else if (ins == CGE)
        current_ins = exec_cge(current_ins, data);
    else if (ins == CLS)
        current_ins = exec_cls(current_ins, data);
    else if (ins == CLE)
        current_ins = exec_cle(current_ins, data);
    else if (ins == CNT)
        current_ins = exec_cnt(current_ins, data);
    else if (ins == COR)
        current_ins = exec_cor(current_ins, data);
    else if (ins == CND)
        current_ins = exec_cnd(current_ins, data);
    else if (ins == RNT)
        current_ins = exec_rnt(current_ins, data);
    else if (ins == RCP)
        current_ins = exec_rcp(current_ins, data);
    else if (ins == RIC)
        current_ins = exec_ric(current_ins, data);
    else
        current_ins++;
    return current_ins;
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
int Program::exec_add(int &current_ins, string data)
{
    double x = pop_d();
    double y = pop_d();

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
int Program::exec_sub(int &current_ins, string data)
{
    double x = pop_d();
    double y = pop_d();

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
int Program::exec_div(int &current_ins, string data)
{
    double x = pop_d();
    double y = pop_d();

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
int Program::exec_mul(int &current_ins, string data)
{
    double x = pop_d();
    double y = pop_d();

    push(y * x);

    if (get_opt("debug"))
        cout << "(debug) " << y << " * " << x << " = " << y * x << endl;

    return ++current_ins;
}

/**
 *  Execute "POW" instruction
 * 
 *  Pop out the two numbers and push the second one at the power of the first one
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_pow(int &current_ins, string data)
{
    double x = pop_d();
    double y = pop_d();

    push(pow(y,x));

    if (get_opt("debug"))
        cout << "(debug) " << y << " ^ " << x << " = " << pow(y, x) << endl;

    return ++current_ins;
}

/**
 *  Execute "INC" instruction
 * 
 *  Pop out the first value of the pile and re-push it plus one
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_inc(int &current_ins, string data)
{
    double x = pop_d();

    push(x + 1);

    return ++current_ins;
}

/**
 *  Execute "DEC" instruction
 * 
 *  Pop out the first value of the pile and re-push it less one
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_dec(int &current_ins, string data)
{
    double x = pop_d();

    push(x - 1);

    return ++current_ins;
}

/**
 *  Execute "NUM" instruction
 * 
 *  Push a number into the pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data The number (as a string) to push to the pile
 *  @returns The next instruction id
 */
int Program::exec_num(int &current_ins, string data)
{
    push(data);

    if (get_opt("debug"))
        cout << "(debug) push: " << data << endl;

    return ++current_ins;
}

/**
 *  Execute "OUT" instruction
 * 
 *  Show a message or the first value of the pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data The message to show, if set to default value, pop a value from the pile
 *  @returns The next instruction id
 */
int Program::exec_out(int &current_ins, string data)
{
    if (data != "0.000000" && data != "")
    {
        cout << data << endl;
    }
    else
    {
        cout << pop() << endl;
    }

    return ++current_ins;
}

/**
 *  Execute "OUL" instruction
 * 
 *  Same as "exec_out" but don't put a line jump
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data The message to show, if set to default value, pop a value from the pile
 *  @returns The next instruction id
 */
int Program::exec_oul(int &current_ins, string data)
{
    if (data != "0.000000" && data != "")
    {
        cout << data;
    }
    else
    {
        cout << pop();
    }

    return ++current_ins;
}

/**
 *  Execute "INP" instruction
 * 
 *  Prompt a value and then push it into the pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data (facultative) The prompt message to show
 *  @returns The next instruction id
 */
int Program::exec_inp(int &current_ins, string data)
{
    string val;
    cout << ((data == "" || data == "0") ? "Value" : data) + ": ";
    cin >> val;

    push(val);

    if (get_opt("debug"))
        cout << "(debug) push: " << val << endl;

    return ++current_ins;
}

/**
 *  Execute "SET" instruction
 * 
 *  Pop the value on top of the pile and put it in the memory
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data The name of the variable
 *  @returns The next instruction id
 * 
 *  NOTE: Find a way to give the type of the variable (eg: data = type + ":" + name)
 */
int Program::exec_set(int &current_ins, string data)
{
    // NOTE: if multiple var type, check the type and don't use pop_d and set_double
    memory.set_double(data, pop_d());

    if (get_opt("debug"))
        cout << "(debug) " << data << " = " << memory.get_double(data) << endl;

    return ++current_ins;
}

/**
 *  Execute "GET" instruction
 * 
 *  Find the value a the variable in the memory and push it in pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data The name of the variable
 *  @returns The next instruction id
 */
int Program::exec_get(int &current_ins, string data)
{
    // NOTE: if multiple var type, check the type and don't use get_double
    double x = memory.get_double(data);

    push(x);

    if (get_opt("debug"))
        cout << "(debug) push: " << x << endl;

    return ++current_ins;
}

/**
 *  EXECUTE "JNZ" instruction
 * 
 *  Pop out the first value of the pile, if this value (as a boolean cast)
 *  is false, then set the current instruction as the one given in data.
 *  Otherwise, go to the next instruction
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Tha instruction id (casted as a string) for the "false" case
 *  @returns The next instruction id
 */
int Program::exec_jnz(int &current_ins, string data)
{
    double x = pop_d();

    current_ins = (x ? (current_ins + 1) : atoi(data.c_str()));

    return current_ins;
}

/**
 *  EXECUTE "JMP" instruction
 * 
 *  Jump to the given instruction id
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Tha instruction id (casted as a string)
 *  @returns The next instruction id 
 */
int Program::exec_jmp(int &current_ins, string data)
{
    current_ins = atoi(data.c_str());

    return current_ins;
}

/**
 *  EXECUTE "CLL" instruction
 * 
 *  Push the next instruction id in the call pile, check if there are enough arguments for
 *  the routine given in data and then jump to it's instruction id
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Tha routine name
 *  @returns The next instruction id 
 */
int Program::exec_cll(int &current_ins, string data) {
    if (routines.find(data) != routines.end())
    {
        c_pile.push_back(current_ins + 1);
        auto r = routines[data];

        if (pile.size() >= r.second)
        {
            reverse(pile.end() - r.second, pile.end());

            return r.first;
        }
        else
        {
            cout << "Not enough arguments, skipped" << endl;
            return ++current_ins;
        }
    }
    
    return ++current_ins;
}

/**
 *  EXECUTE "RTR" instruction
 * 
 *  Go back to last instruction id of the call pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case
 *  @returns The next instruction id 
 */
int Program::exec_rtr(int &current_ins, string data) {
    return current_ins = pop_c();
}

/**
 *  EXECUTE "PLT" instruction
 * 
 *  Plot a draw from it's routine name
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data The routine name
 *  @returns The next instruction id 
 */
int Program::exec_plt(int &current_ins, string data) {
    vector<string> d = read_data(data);
    vector<string> args;

    string routine = d.size() > 0 ? d[0] : ":noroutine:";

    //   -1: no args and no xmin/xmax/xoff
    //    0: no args but xmin/xmax/xoff
    //n > 0: n args and xmin/xmax/xoff
    int nb_args = d.size() > 1 ? atof(d[1].c_str()) : -1;

    // fetch args
    if(nb_args > 0) {
        for(int i = 0; i < nb_args; i++) args.push_back(pop());
    }

    reverse(args.begin(), args.end());

    // find xmin, xmax, xoff
    double xoff = (nb_args >= 0) ? pop_d() : 0.1;
    double xmax = (nb_args >= 0) ? pop_d() : 10;
    double xmin = (nb_args >= 0) ? pop_d() : -10;

    // check if the routine exists
    if (routines.find(routine) == routines.end())
    {
        cout << "Routine is not defined." << endl;
        return ++current_ins;
    }

    // check for the args amount
    if (routines[routine].second > args.size() + 1)
    {
        cout << "Plot need " << routines[routine].second - 1 << " parameters for this routine." << endl;
        return ++current_ins;
    }

    vector<pair<double, double>> points;

    for (double x = xmin; x <= xmax; x += xoff)
    {
        // Push x
        push(x);
        // Push args
        for (auto &a : args) push(a);

        // Get first instruction line
        int line = 0;
        line     = exec_cll(line, routine);

        Instruction instr;

        do {        
            // Fetch instruction
            auto current = instructions[line];
            instr = current.first;
            string instr_data = current.second;

            // Execute it and get new line
            line = exec(instr, line, instr_data);  
        } while(instr != RTR);

        // Pop y
        double y = pop_d();
        points.push_back(make_pair(x, y));
    }

    // Plot point
    plot(points);

    return ++current_ins;
}

/**
 *  Execute "CEQ" instruction
 * 
 *  Pop out the two first values of the pile, and then push the result of the comparaison
 *      (1 if x = y, 0 otherwise)
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_ceq(int &current_ins, string data)
{

    double x = pop_d();
    double y = pop_d();

    push(x == y);

    return ++current_ins;
}

/**
 *  Execute "CGR" instruction
 * 
 *  Pop out the two first values of the pile, and then push the result of the comparaison
 *      (1 if y > x, 0 otherwise)
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_cgr(int &current_ins, string data)
{

    double x = pop_d();
    double y = pop_d();

    push(y > x);

    return ++current_ins;
}

/**
 *  Execute "CGE" instruction
 * 
 *  Pop out the two first values of the pile, and then push the result of the comparaison
 *      (1 if y >= x, 0 otherwise)
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_cge(int &current_ins, string data)
{

    double x = pop_d();
    double y = pop_d();

    push(y >= x);

    return ++current_ins;
}

/**
 *  Execute "CLS" instruction
 * 
 *  Pop out the two first values of the pile, and then push the result of the comparaison
 *      (1 if y < x, 0 otherwise)
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_cls(int &current_ins, string data)
{

    double x = pop_d();
    double y = pop_d();

    push(y < x);

    return ++current_ins;
}

/**
 *  Execute "CLE" instruction
 * 
 *  Pop out the two first values of the pile, and then push the result of the comparaison
 *      (1 if y <= x, 0 otherwise)
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_cle(int &current_ins, string data)
{

    double x = pop_d();
    double y = pop_d();

    push(y <= x);

    return ++current_ins;
}

/**
 *  Execute "CNT" instruction
 * 
 *  Pop out the first value of the pile, and then push it's boolean inverse
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_cnt(int &current_ins, string data)
{

    double x = pop_d();

    push(!x);

    return ++current_ins;
}

/**
 *  Execute "COR" instruction
 * 
 *  Pop out the two first values of the pile, and then push the result of the boolean large
 *      OR (x || y) operation
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_cor(int &current_ins, string data)
{

    double x = pop_d();
    double y = pop_d();

    push(y || x);

    return ++current_ins;
}

/**
 *  Execute "CND" instruction
 * 
 *  Pop out the two first values of the pile, and then push the result of the boolean large
 *      AND (x && y) operation
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_cnd(int &current_ins, string data)
{

    double x = pop_d();
    double y = pop_d();

    push(y && x);

    return ++current_ins;
}

/**
 *  Execute "RNT" instruction
 * 
 *  Pop out the two first values of the pile, and then push them in the for pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_rnt(int &current_ins, string data)
{
    int n = (int)pop_d();
    int i = (int)pop_d();

    f_push(i, n);

    return ++current_ins;
}

/**
 *  Execute "RCP" instruction
 * 
 *  Pop out the first value of the for pile, check if i is greater then n and then
 *      push the result of the comparaison in the pile
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_rcp(int &current_ins, string data)
{
    auto f = f_pop();

    if (f.first > f.second)
    {
        push(0);
    }
    else
    {
        f_push(f.first, f.second);
        push(1);
    }

    memory.set_double(data, f.first);

    return ++current_ins;
}

/**
 *  Execute "RIC" instruction
 * 
 *  Pop out the first value of the for pile, add 1 to i and then push it back
 * 
 *  @param current_ins The id of the current instruction in the instruction vector
 *  @param data Useless in this case, uniformity
 *  @returns The next instruction id
 */
int Program::exec_ric(int &current_ins, string data)
{
    auto f = f_pop();

    f_push(f.first + 1, f.second);

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
    if (prog.get_opt("bienvenue"))
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
        os << "│ " << setw(5) << i++ << setw(13) << name(ins.first) << setw(20) << ins.second << " │" << endl;
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
 *  @returns The first value of the pile as a string
 */
string Program::pop()
{
    if (pile.size() == 0)
        return 0;

    string val = pile[pile.size() - 1];

    pile.pop_back();

    return val;
}

/**
 *  Push a value on top of the pile
 * 
 *  @param data The value to push in the pile
 */
void Program::push(string data)
{
    pile.push_back(data);
}

/**
 *  Pop out the first value of the pile as a double
 * 
 *  @returns The first value of the pile as a double
 */
double Program::pop_d()
{
    return atof(pop().c_str());
}

/**
 *  Push a double on top of the pile
 * 
 *  @param data The double value to push in the pile
 */
void Program::push(double data)
{
    push(to_string(data));
}

/**
 *  Push values inside the for pile
 * 
 *  @param i The iterator of the for
 *  @param n The max value of the for
 */
void Program::f_push(int i, int n)
{
    f_pile.push_back(make_pair(i, n));
}

/**
 *  Pop out the first pair of the for pile
 * 
 *  @returns The iterator and the max value
 */
pair<int, int> Program::f_pop()
{
    if (f_pile.size() == 0)
        return make_pair(0, 0);

    auto val = f_pile[f_pile.size() - 1];

    f_pile.pop_back();

    return val;
}

/**
 *  Pop out the first element of the call pile
 * 
 *  @returns The last instruction id in the pile
 */
int Program::pop_c()
{
    auto val = c_pile[c_pile.size() - 1];

    c_pile.pop_back();

    return val;
}

//
// ────────────────────────────────────────────────────────── PRIVATE METHODS ─────
//