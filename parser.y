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

%}

%union {
    double number;
    char* name;
    bool boolean;
}

%token <number> NUMBER
%token <name> IDENTIFIER
%token <boolean> BOOL

%token LBRACKET
%token RBRACKET
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
    | calcul                    { if(prog.get_opt("show_results")) prog.ins(OUT, 0); }
    | option
    | instruction END_OF_LINE
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

    // Show and write execution commands
    cout << prog << endl;
    prog.write("output.exec");

    // Run the program
    prog.run();

    return 0;
}

int yyerror(char const *s) {					
    cout << "[ERROR]" << s << endl;

    return 1;
}