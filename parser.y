%{
    #include <iostream>
    #include <cmath>
    #include <string>
    using namespace std;

    #include "./src/VarManager.h"

    extern int yylex();
    int yyerror(char const *s);

    VarManager vm;
%}

%union {
    double number;
    char* string;
}

%token <number> NUMBER
%token <string> STRING
%token <string> VARIABLE
%token LET
%token EQUAL
%token SHOW
%token GET
%token END_OF_LINE
%token SEMI
%type <number> calcul
%type <string> expression
%left PLUS MINUS
%left TIMES DIVIDE

%%
main: /* empty */
    | main statement
    ;

statement: calcul
    | expression
    | statement SEMI
    | statement END_OF_LINE
    | LET VARIABLE EQUAL calcul { vm.set_double($2, $4); }
    | SHOW calcul               { cout << $2 << endl; }
    | SHOW VARIABLE             { 
        if(vm.is_set($2)) cout << $2 << " = " << setprecision(10) <<  vm.get_double($2) << endl;
        else cout << $2 << " is not defined" << endl;
    }
    | SHOW STRING               { cout << $2 << endl; }
    | GET VARIABLE              { double var; cout << $2 << " = "; cin >> var; vm.set_double($2, var); }
    ;

calcul:
    NUMBER                      { $$ = $1; }
    | VARIABLE                  { $$ = vm.get_double($1); }
    | MINUS NUMBER              { $$ = -$2; }
    | calcul MINUS calcul       { $$ = $1 - $3; }
    | calcul PLUS calcul        { $$ = $1 + $3; }
    | calcul TIMES calcul       { $$ = $1 * $3; }
    | calcul DIVIDE calcul      { $$ = $1 / $3; }
    ;

expression:
    STRING                      { $$ = $1; cout << $$ << endl; }
    ;


%%

void welcome() {
    cout << "┌────────────────────────────────────────┐" << endl;
    cout << "│                                        │" << endl;
    cout << "│               GalenaC++                │" << endl;
    cout << "│                                        │" << endl;
    cout << "├────────────────────────────────────────┤" << endl;
    cout << "│                                        │" << endl;
    cout << "│                    \\\\                  │" << endl;
    cout << "│                    (o>                 │" << endl;
    cout << "│                \\\\_//)                  │" << endl;
    cout << "│                 \\_/_)                  │" << endl;
    cout << "│                  _|_                   │" << endl;
    cout << "│                       v1.0.0           │" << endl;
    cout << "├────────────────────────────────────────┤" << endl;
    cout << "│ © Copyright 2019 - ARBACHE - MIQUET    │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
    cout << endl << endl;
}

int main(int argc, char **argv) {

    // Try to open given file
    if(argc > 1) {
        FILE *file = fopen(argv[1], "r");

        if(file == NULL || !file) {
            cout << "Unable to read file \"" << argv[1] << "\", running interactive"  << endl;
        } else {
            cout << "Reading \"" << argv[1] << "\"" << endl;
            yyin = file;
        }
    }

    // Welcome
    welcome();

    // Parse
    yyparse();

    return 0;
}

int yyerror(char const *s) {					
    cout << "[ERROR]" << s << endl;

    return 1;
}