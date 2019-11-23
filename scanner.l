%{
    extern "C" int yylex();
    #include "./src/str/str.h"
    #include "parser.tab.c"
%}

%option noyywrap

%%

"="                             { return EQUAL; }
"("                             { return LBRACKET; }
")"                             { return RBRACKET; }
":"                             { return COLON; }
"+"                             { return PLUS; }
"-"                             { return MINUS; }
"*"                             { return TIMES; }
"/"                             { return DIVIDE; }
"++"                            { return INCREMENT; }
"--"                            { return DECREMENT; }
";"                             { return SEMI; }
"%option"                       { return OPTION; }
"true"|"false"|"vrai"|"faux"    { yylval.boolean = !((strcmp(yytext, "true")) && (strcmp(yytext, "vrai"))); return BOOL; }
"afficher"                      { return OUTPUT; }
"afficherl"                     { return OUTPUTL; }
"saisir"                        { return INPUT; }
"si"|"SI"|"Si"                  { return IF; }
"alors"|"ALORS"|"Alors"         { return THEN; }
"sinon"|"SINON"|"Sinon"         { return ELSE; }
"fin"|"FIN"|"Fin"               { return END; }
"=="|"egal"|"Egal"|"EGAL"       { return IS_EQUAL; }
">"                             { return IS_GREATER; }
">="                            { return IS_GREATER_EQUAL; }
"<"                             { return IS_LESS; }
"<="                            { return IS_LESS_EQUAL; }
"non"|"NON"|"Non"               { return NOT; }
"ou"|"OU"|"Ou"                  { return OR; }
"et"|"ET"|"Et"                  { return AND; }
"tant que"|"TANT QUE"|"Tant Que"    { return WHILE; }
"faire"|"FAIRE"|"Faire"         { return DO; }
"répéter"|"REPETER"|"Répéter"   { return REPEAT; }
([0-9]+(\.[0-9]*)?)|(\.[0-9])   { yylval.number = atof(yytext); return NUMBER; }
[A-Za-z_][0-9A-Za-z_]*          { yylval.name = strdup(yytext); return IDENTIFIER; }
[\"].*[\"]                      { yylval.name = trim(strdup(yytext), '"'); return STRING; }
[ \t]                           ;
\/\/.*                          ;
\n                              { return END_OF_LINE; }
<<EOF>>                         { static int once = 0; return once++ ? 0 : END_OF_LINE; }

%%