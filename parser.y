%{
    #include <iostream>
    #include <cmath>
    #include <string>
    using namespace std;

    extern int yylex();
    int yyerror(char const *s);
%}

%code requires{
    #define YYSTYPE string
}

%token IDENTIFIER
%token END_OF_LINE
%left OR
%left AND

%%
main: /* empty */
    | main statement
    ;

statement: expression
    | statement END_OF_LINE
    ;

expression:
    IDENTIFIER                  { $$ = $1; cout << $1 << endl; }
    | expression OR expression  { $$ = $1 + " or " + $3; cout << $1 << " or " << $3 << endl; }
    | expression AND expression { $$ = $1 + " and " + $3; cout << $1 << " and " << $3 << endl; }
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