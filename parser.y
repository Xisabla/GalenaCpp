%{
    #include <iostream>
    #include <iomanip>
    #include <map>
    #include <string>
    #include <vector>
    
    #include "./src/program/program.h"

    using namespace Instructions;
    using namespace std;

    extern int yylex();
    int yyerror(char const *s);

    // Intialize program
    Program prog;
    bool err = false;
    static int line = 1;

%}

%union {
    double number;
    char* name;
    bool boolean;
    t_targeter targeter;
}

%token <number> NUMBER
%token <name> IDENTIFIER
%token <boolean> BOOL
%token <targeter> IF
%token THEN
%token ELSE
%token ENDIF

%token EQUAL
%token LBRACKET
%token RBRACKET
%token OUTPUT
%token INPUT
%token END_OF_LINE
%token SEMI
%token OPTION
%token IS_EQUAL
%token IS_GREATER
%token IS_GREATER_EQUAL
%token IS_LESS
%token IS_LESS_EQUAL
%token OR
%token AND


%left PLUS MINUS
%left TIMES DIVIDE

%%

main: main instruction END_OF_LINE  { line++; }
    |
    ;

instruction: /* empty */
    | option
    | calcul                    { if(prog.get_opt("show_results")) prog.ins(OUT, 0); }
    | io
    | IDENTIFIER EQUAL calcul   { prog.ins(SET, $1); }
    | IF condition END_OF_LINE  { $1.ic_goto = prog.ic(); prog.ins(JNZ, 0); }
      THEN END_OF_LINE main     { $1.ic_false = prog.ic(); prog.ins(JMP, 0); prog[$1.ic_goto] = to_string(prog.ic()); }
      ELSE END_OF_LINE main     { prog[$1.ic_false] = to_string(prog.ic()); }
      ENDIF                     { }
    | instruction END_OF_LINE   { line++; }
    | instruction SEMI;
    ;

condition:
    calcul                              { }
    | calcul IS_EQUAL calcul            { prog.ins(CMPEQU, 0); }
    | calcul IS_GREATER calcul          { prog.ins(CMPGTR, 0); }
    | calcul IS_GREATER_EQUAL calcul    { prog.ins(CMPGTE, 0); }
    | calcul IS_LESS calcul             { prog.ins(CMPLSS, 0); }
    | calcul IS_LESS_EQUAL calcul       { prog.ins(CMPLSE, 0); }
    | condition OR condition            { prog.ins(CMPOR, 0); }
    | condition AND condition           { prog.ins(CMPAND, 0); }
    ;

option: 
    OPTION IDENTIFIER           { prog.set_opt($2); }
    | OPTION IDENTIFIER BOOL    { prog.set_opt($2, $3); }
    ;

calcul:
    calcul PLUS calcul          { prog.ins(ADD, 0); }
    | calcul MINUS calcul       { prog.ins(SUB, 0); }
    | calcul TIMES calcul       { prog.ins(MUL, 0); }
    | calcul DIVIDE calcul      { prog.ins(DIV, 0); }
    | LBRACKET calcul RBRACKET  { }
    | MINUS NUMBER              { prog.ins(NUM, -$2); }
    | NUMBER                    { prog.ins(NUM, $1); }
    | IDENTIFIER                { prog.ins(GET, $1); }
    ;

io:
    INPUT IDENTIFIER            { prog.ins(INP, $2); prog.ins(SET, $2); }
    | OUTPUT calcul             { prog.ins(OUT, 0); }
    ;
%%

int main(int argc, char **argv) {

    // Try to open given file
    if(argc > 1) {
        FILE *file = fopen(argv[1], "r");

        if(file && file != NULL)
            yyin = file;
    }

    // Parse
    yyparse();

    if(err) {
        return 1;
    }

    // Show and write execution commands
    cout << prog << endl;

    // Run the program
    prog.run();

    return 0;
}

int yyerror(char const *s) {					
    cout << "Error at line " << line << ": " << s << endl;

    err = true;

    return 1;
}