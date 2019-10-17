%{
    #include <iostream>
    #include <cmath>
    #include <string>
    using namespace std;

    extern int yylex();
    int yyerror(char *s);
%}

%code requires{
    #define YYSTYPE double
}

%token NOMBRE
%token RETOUR_LIGNE
%left PLUS

%%
main: /* empty */
    | main statement
    ;

statement: expression RETOUR_LIGNE

expression:
    NOMBRE              { $$ = $1; }
    | expression PLUS expression  { $$ = $1 + $3; cout << $1 << " + " << $2 << " = " << $$ << endl; }
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