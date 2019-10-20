%{
    extern "C" int yylex();
    
    #include <iostream>
    #include "parser.tab.c"
%}

%option noyywrap

%%

"afficher"                      { return SHOW; }
"soit"                          { return LET; }
"="                             { return EQUAL; }
"+"                             { return PLUS; }
"-"                             { return MINUS; }
"*"                             { return TIMES; }
"/"                             { return DIVIDE; }
";"                             { return SEMI; }
([0-9]+(\.[0-9]*)?)|(\.[0-9])   { yylval.number = atof(yytext); return NUMBER; }
\"[a-zA-Z0-9_ ]*\"              { yylval.string = strdup(yytext); return STRING; }
[a-zA-Z0-9_]+                   { yylval.string = strdup(yytext); return VARIABLE; }
[ \t]                           ;
\n                              { return END_OF_LINE; }
<<EOF>>                         { static int once = 0; return once++ ? 0 : END_OF_LINE; }

%%