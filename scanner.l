%{
    extern "C" int yylex();
    
    #include <iostream>
    #include "parser.tab.c"
%}

%option noyywrap
%option nounput

%%

"|"                             { return OR; }
"&"                             { return AND; }
[a-z]+                          { yylval = yytext; return IDENTIFIER; }
[ \t]                           ;
\/\/.*                          ;
\n                              { return END_OF_LINE; }
<<EOF>>                         { static int once = 0; return once++ ? 0 : END_OF_LINE; }

%%