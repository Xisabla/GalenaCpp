%{
    extern "C" int yylex();
    
    #include "parser.tab.c"
%}

%option noyywrap

%%

"("                             { return LBRACKET; }
")"                             { return RBRACKET; }
"+"                             { return PLUS; }
"-"                             { return MINUS; }
"*"                             { return TIMES; }
"/"                             { return DIVIDE; }
";"                             { return SEMI; }
([0-9]+(\.[0-9]*)?)|(\.[0-9])   { yylval.number = atof(yytext); return NUMBER; }
[ \t]                           ;
\/\/.*                          ;
\n                              { return END_OF_LINE; }
<<EOF>>                         { static int once = 0; return once++ ? 0 : END_OF_LINE; }

%%