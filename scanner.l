%{
    extern "C" int yylex();
    
    #include <iostream>
    #include "parser.tab.c"
%}

%option noyywrap

%%

([0-9]+(\.[0-9]*)?)|(\.[0-9])   { yylval = atof(yytext); return NOMBRE; }
"+"                             { return PLUS; }
\n                              { return RETOUR_LIGNE; }
<<EOF>>                         { static int once = 0; return once++ ? 0 : RETOUR_LIGNE; }

%%