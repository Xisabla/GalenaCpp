%{
    #include <iostream>
    #include <cmath>
    #include <string>
    using namespace std;

    #include "./src/vars.h"

    varman* vm = init_vm();

    extern int yylex();
    int yyerror(char *s);
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
    | LET VARIABLE EQUAL calcul { setvar_f(vm, strdup($2), $4); cout << "let " << $2 << " = " << getvar_f(vm, strdup($2)).v << endl; }
    | SHOW calcul               { cout << $2 << endl; }
    | SHOW VARIABLE             { show_var_f(vm, strdup($2)); }
    | SHOW STRING               { cout << $2 << endl; } 
    ;

calcul:
    NUMBER                      { $$ = $1; }
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

    // Parse
    yyparse();	

    return 0;
}

int yyerror(char *s) {					
    cout << "[ERROR]" << s << endl;

    return 1;
}