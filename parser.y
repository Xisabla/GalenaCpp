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
}

%token <number> NUMBER
%type <number> calcul

%token END_OF_LINE
%token SEMI
%token LBRACKET
%token RBRACKET


%left PLUS MINUS
%left TIMES DIVIDE

%%

main: 
    | main instruction
    ;

instruction: calcul             {  }     
    | instruction END_OF_LINE
    | instruction SEMI;
    ;

calcul: calcul PLUS calcul      { prog.ins(ADD, 0); }
    | calcul MINUS calcul       { prog.ins(SUB, 0); }
    | calcul TIMES calcul       { prog.ins(DIV, 0); }
    | calcul DIVIDE calcul      { prog.ins(MUL, 0); }
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