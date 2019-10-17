%{
    extern "C" int yylex();
    
    #include <iostream>
    #include "parser.tab.c"
%}

%option noyywrap

%%

([0-9]+(\.[0-9]*)?)|(\.[0-9])   { yylval.number = atof(yytext); return NUMBER; }
"+"                             { return PLUS; }
"-"                             { return MINUS; }
"*"                             { return TIMES; }
"/"                             { return DIVIDE; }
"="                             { return EQUAL; }
"let"                           { return VAR_DEFINER; }
"show"                          { return SHOW; }
";"                             { return SEMI; }
[a-zA-Z0-9_]+                   { yylval.string = strdup(yytext); return STRING; }
[ \t]                           ;
\n                              { return END_OF_LINE; }
<<EOF>>                         { static int once = 0; return once++ ? 0 : END_OF_LINE; }

%%