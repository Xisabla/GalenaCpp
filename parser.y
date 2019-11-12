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
}

%token <number> NUMBER
%token <name> IDENTIFIER
%token <boolean> BOOL

%token EQUAL
%token LBRACKET
%token RBRACKET
%token OUTPUT
%token INPUT
%token END_OF_LINE
%token SEMI
%token OPTION


%left PLUS MINUS
%left TIMES DIVIDE

%%

main: /* empty */
    | main instruction
    ;

instruction: /* empty */
    | option
    | calcul                    { if(prog.get_opt("show_results")) prog.ins(OUT, 0); }
    | io
    | IDENTIFIER EQUAL calcul   { prog.ins(SET, $1); }
    | instruction END_OF_LINE   { line++; }
    | instruction SEMI;
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
    ;

io:
    INPUT IDENTIFIER            { prog.ins(INP, $2); prog.ins(SET, $2); }
    | OUTPUT calcul             { prog.ins(OUT, 0); }
    | OUTPUT IDENTIFIER         { prog.ins(GET, $2); prog.ins(OUT, $2); }
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