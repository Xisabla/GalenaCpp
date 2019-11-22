%{
    extern "C" int yylex();
    
    #include "parser.tab.c"
%}

%option noyywrap

%%

"="                             { return EQUAL; }
"("                             { return LBRACKET; }
")"                             { return RBRACKET; }
"+"                             { return PLUS; }
"-"                             { return MINUS; }
"*"                             { return TIMES; }
"/"                             { return DIVIDE; }
";"                             { return SEMI; }
"%option"                       { return OPTION; }
"true"|"false"|"vrai"|"faux"    { yylval.boolean = !((strcmp(yytext, "true")) && (strcmp(yytext, "vrai"))); return BOOL; }
"afficher"                      { return OUTPUT; }
"saisir"                        { return INPUT; }
"si"|"SI"|"Si"                  { return IF; }
"alors"|"ALORS"|"Alors"         { return THEN; }
"sinon"|"SINON"|"Sinon"         { return ELSE; }
"finsi"|"FINSI"|"FinSi"         { return ENDIF; }
"=="|"egal"|"Egal"|"EGAL"       { return IS_EQUAL; }
">"                             { return IS_GREATER; }
">="                            { return IS_GREATER_EQUAL; }
"<"                             { return IS_LESS; }
"<="                            { return IS_LESS_EQUAL; }
"non"|"NON"|"Non"               { return NOT; }
"ou"|"OU"|"Ou"                  { return OR; }
"et"|"ET"|"Et"                  { return AND; }
([0-9]+(\.[0-9]*)?)|(\.[0-9])   { yylval.number = atof(yytext); return NUMBER; }
[A-Za-z_][0-9A-Za-z_]*          { yylval.name = strdup(yytext); return IDENTIFIER; }
[ \t]                           ;
\/\/.*                          ;
\n                              { return END_OF_LINE; }
<<EOF>>                         { static int once = 0; return once++ ? 0 : END_OF_LINE; }

%%