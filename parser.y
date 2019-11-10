%{
    #include <iostream>
    #include <iomanip>
    #include <map>
    #include <string>
    #include <vector>
    #include "./src/program/program.h"

    using namespace std;

    extern int yylex();
    int yyerror(char const *s);

    Program prog;

    int nb_inst = 0;
    vector<pair<int, double>> instructions;

    inline int ins(int c, double d) { instructions.push_back(make_pair(c, d)); return nb_inst++; }

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

calcul: calcul PLUS calcul      { prog.ins(PLUS, 0); }
    | calcul MINUS calcul       { prog.ins(MINUS, 0); }
    | calcul TIMES calcul       { prog.ins(TIMES, 0); }
    | calcul DIVIDE calcul      { prog.ins(DIVIDE, 0); }
    | LBRACKET calcul RBRACKET  { }
    | MINUS NUMBER              { prog.ins(NUMBER, -$2); }
    | NUMBER                    { prog.ins(NUMBER, $1); }
    ;

%%

int main(int argc, char **argv) {

    // Try to open given file
    if(argc > 1) {
        FILE *file = fopen(argv[1], "r");

        if(file && file != NULL)
            yyin = file;
    }

    prog.set_tokens({
        { PLUS, "ADD" },
        { MINUS, "SUB" },
        { DIVIDE, "DIV" },
        { TIMES, "MUL" },
        { NUMBER, "NUM" }
    });

    yyparse();

    cout << prog << endl;

    prog.write("output.exec");
    prog.run();

    return 0;
}

int yyerror(char const *s) {					
    cout << "[ERROR]" << s << endl;

    return 1;
}