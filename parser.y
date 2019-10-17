%{
    #include <iostream>
    #include <cmath>
    #include <string>
    using namespace std;

    extern int yylex();
    int yyerror(char *s);

    // TODO: Use chained list, or something else - but simplified functions with more complex objects

    typedef struct varDouble {
        char* name;
        double value;
    } varDouble;

    varDouble *vDouble = (varDouble *)malloc(sizeof(varDouble));
    int varId = 0;

    // TODO: Ofc use another lib for that

    bool createrVarDouble(string name, double value);
    bool assignVarDouble(string name, double value);
    varDouble* getVarDouble(string name);
    double getVarDoubleValue(string name);

%}

%union {
    double number;
    char* string;
}

%token <number> NUMBER
%token <string> STRING
%token VAR_DEFINER
%token SHOW
%token EQUAL
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
    | VAR_DEFINER STRING EQUAL calcul   { string s = $2; assignVarDouble(s, $4); }
    | SHOW STRING                     { string s = $2; cout << s << " = " << getVarDoubleValue(s) << endl; }
    /*| VAR_DEFINER STRING EQUAL calcul   { varId++; varsVal[varId] = $4; cout << "Set " << $2 << " = " << varsVal[varId] << " (id: " << varId << ")" << endl;  }*/
    ;

calcul:
    NUMBER                  { $$ = $1; }
    | MINUS NUMBER          { $$ = -$2; }
    | calcul MINUS calcul   { $$ = $1 - $3; cout << $1 << " - " << $3 << " = " << $$ << endl; }
    | calcul PLUS calcul    { $$ = $1 + $3; cout << $1 << " + " << $3 << " = " << $$ << endl; }
    | calcul TIMES calcul   { $$ = $1 * $3; cout << $1 << " * " << $3 << " = " << $$ << endl; }
    | calcul DIVIDE calcul  { $$ = $1 / $3; cout << $1 << " / " << $3 << " = " << $$ << endl; }
    ;

expression:
    STRING                      { $$ = $1; string s = $1; cout << "String: " << s << endl; }
    ;


%%

varDouble* getVarDouble(string name) {

   for(int i = 0; i < varId; i++) {
        string vname = vDouble[i].name;

        if(name == vname) {
            return vDouble;
        }
    }

    return NULL;

}

double getVarDoubleValue(string name) {

    varDouble* var = getVarDouble(name);

    return var == NULL ? 0 : var->value;

}

bool createrVarDouble(string name, double value) {

    // Create variable
    varDouble v;
    v.name = strdup(name.c_str());
    v.value = value;

    // Set it
    vDouble[varId] = v;

    // Tell it
    cout << "Create (id: " << varId << ")" << v.name << " = (float)" << v.value << endl;

    // Expand var container
    vDouble = (varDouble*)realloc(vDouble, (varId + 2) * sizeof(varDouble));

    varId++;

    return (vDouble != NULL);

}

bool assignVarDouble(string name, double value) {

    varDouble* var = getVarDouble(name);

    // If the variable already exists
    if(var != NULL) {

        var->value = value;
        
        cout << "Edit " << var->name << " = (float)" << var->value << endl;

        return true;

    }

    return createrVarDouble(name, value);

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

    // Parse
    yyparse();	

    return 0;
}

int yyerror(char *s) {					
    cout << "[ERROR]" << s << endl;

    return 1;
}