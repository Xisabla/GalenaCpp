%{
    #define YYERROR_VERBOSE
    
    #include "./src/program/program.h"
    #include "./src/plot/plot.h"

    using namespace Instructions;
    using namespace std;

    extern int yylex();
    int yyerror(char const *s);

    // Intialize program
    Program prog;
    bool p_err = false;

    static int line = 1;
    static int nb_args = 0;


%}

%union {
    double number;
    char* name;
    bool boolean;
    t_targeter targeter;
}

// Values tokens
%token <number> NUMBER
%token <name> IDENTIFIER
%token <name> STRING
%token <boolean> BOOL

// Simple instructions
%token OPTION
%token OUTPUT
%token OUTPUTL
%token INPUT
%token RETURN
%token CALL
%token PLOT

// Block/Loop tokens
%token <targeter> IF
%token <targeter> WHILE
%token <targeter> REPEAT
%token THEN
%token ELSE
%token DO
%token END

// Condition tokens
%token IS_EQUAL
%token IS_GREATER
%token IS_GREATER_EQUAL
%token IS_LESS
%token IS_LESS_EQUAL
%token NOT
%token OR
%token AND

// Seperators
%token EQUAL
%token LBRACKET
%token RBRACKET
%token COMMA
%token <targeter> COLON
%token END_OF_LINE
%token SEMI

// Operatators
%token INCREMENT
%token DECREMENT
%left PLUS MINUS
%left TIMES DIVIDE
%left POWER

%%

main: main instruction END_OF_LINE  { line++; }
    | main instruction SEMI
    |
    ;

instruction: /* empty */
    | option
    | calcul                            { if(prog.get_opt("voir_reulstats")) prog.ins(OUT, 0); }
    | io
    | IDENTIFIER EQUAL calcul           { prog.ins(SET, $1); }
    | IF condition END_OF_LINE          {
                                            $1.ic_goto = prog.ic();
                                            prog.ins(JNZ, 0); }
      THEN END_OF_LINE main             {
                                            $1.ic_false = prog.ic();
                                            prog.ins(JMP, 0);
                                            prog[$1.ic_goto] = to_string(prog.ic()); }
      ELSE END_OF_LINE main             { prog[$1.ic_false] = to_string(prog.ic()); }
      END                               { }
    | WHILE                             { $1.ic_false = prog.ic(); }
      condition END_OF_LINE             {
                                            $1.ic_goto = prog.ic();
                                            prog.ins(JNZ, 0); }
      DO END_OF_LINE main               {
                                            prog.ins(JMP, $1.ic_false);
                                            prog[$1.ic_goto] = to_string(prog.ic()); }
      END                               { }
    | REPEAT IDENTIFIER EQUAL calcul COLON calcul END_OF_LINE {
                                            prog.ins(RNT, 0);
                                            $1.ic_goto = prog.ic();
                                            prog.ins(RCP, $2);
                                            $1.ic_false = prog.ic();
                                            prog.ins(JNZ, 0); }
      DO END_OF_LINE main               { 
                                            prog.ins(RIC, 0);
                                            prog.ins(JMP, $1.ic_goto);
                                            prog[$1.ic_false] = to_string(prog.ic()); }
      END 
    | IDENTIFIER COLON                  {
                                            $2.ic_goto = prog.ic();
                                            prog.ins(JMP, 0); }
      args END_OF_LINE                  { prog.set_routine($1, $2.ic_goto + 1, nb_args); }
      main                              { }
      return                            { prog[$2.ic_goto] = to_string(prog.ic()); }
    | call                              { }
    | PLOT IDENTIFIER                   {
        string data = string($2) + ":-1"; 
        prog.ins(PLT, data);
    }
    | PLOT IDENTIFIER calcul calcul calcul {
        string data = string($2) + ":0";
        prog.ins(PLT, data);
    }
    | PLOT IDENTIFIER calcul calcul calcul call_args {
        string data = string($2) + ":" + to_string(nb_args);
        prog.ins(PLT, data);
    }
    ;

args:
    args COMMA IDENTIFIER               { prog.ins(SET, $3); nb_args++; }
    | IDENTIFIER                        { prog.ins(SET, $1); nb_args = 1; }
    |                                   { nb_args = 0; }
    ;

call:
    CALL IDENTIFIER                     { prog.ins(CLL, $2); }
    | CALL IDENTIFIER call_args         { prog.ins(CLL, $2); }
    ;

call_args:
    | calcul                            { nb_args = 1; }
    | calcul COMMA call_args            { nb_args++; }
    |                                   { nb_args = 0; }
    ;

return:
    RETURN                              { prog.ins(RTR, 0); }
    | RETURN calcul                     { prog.ins(RTR, 0); }
    ;

condition:
    calcul                              { }
    | NOT condition                     { prog.ins(CNT, 0); }
    | calcul IS_EQUAL calcul            { prog.ins(CEQ, 0); }
    | calcul IS_GREATER calcul          { prog.ins(CGR, 0); }
    | calcul IS_GREATER_EQUAL calcul    { prog.ins(CGE, 0); }
    | calcul IS_LESS calcul             { prog.ins(CLS, 0); }
    | calcul IS_LESS_EQUAL calcul       { prog.ins(CLE, 0); }
    | condition OR condition            { prog.ins(COR, 0); }
    | condition AND condition           { prog.ins(CND, 0); }
    ;

option: 
    OPTION IDENTIFIER                   { prog.set_opt($2); }
    | OPTION IDENTIFIER BOOL            { prog.set_opt($2, $3); }
    ;

calcul:
    calcul PLUS calcul                  { prog.ins(ADD, 0); }
    | calcul MINUS calcul               { prog.ins(SUB, 0); }
    | calcul TIMES calcul               { prog.ins(MUL, 0); }
    | calcul DIVIDE calcul              { prog.ins(DIV, 0); }
    | calcul POWER calcul               { prog.ins(POW, 0); }
    | calcul INCREMENT                  { prog.ins(INC, 0); }
    | calcul DECREMENT                  { prog.ins(DEC, 0); }
    | LBRACKET calcul RBRACKET          { }
    | MINUS calcul                      { prog.ins(NUM, -1); prog.ins(MUL, 0); }
    | NUMBER                            { prog.ins(NUM, $1); }
    | IDENTIFIER INCREMENT              { prog.ins(GET, $1);prog.ins(INC, 0); prog.ins(SET, $1); prog.ins(GET, $1); }
    | IDENTIFIER                        { prog.ins(GET, $1); }
    | call                              { }
    ;

io:
    INPUT IDENTIFIER                    { prog.ins(INP, $2); prog.ins(SET, $2); }
    | OUTPUTL condition                 { prog.ins(OUL, 0); }   
    | OUTPUTL calcul                    { prog.ins(OUL, 0); }
    | OUTPUTL STRING                    { prog.ins(OUL, $2); }
    | OUTPUT condition                  { prog.ins(OUT, 0); }   
    | OUTPUT calcul                     { prog.ins(OUT, 0); }
    | OUTPUT STRING                     { prog.ins(OUT, $2); }
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

    if(p_err) {
        return 1;
    }

    // Run the program
    prog.run();

    return 0;
}

int yyerror(char const *s) {					
    cout << "Error at line " << line << ": " << s << endl;

    p_err = true;

    return 1;
}