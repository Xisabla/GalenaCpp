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
"%option"                       { return OPTION; }
"true"|"false"                  { yylval.boolean = !(strcmp(yytext, "true")); return BOOL; }
([0-9]+(\.[0-9]*)?)|(\.[0-9])   { yylval.number = atof(yytext); return NUMBER; }
[A-Za-z_][0-9A-Za-z_]*          { yylval.name = strdup(yytext); return IDENTIFIER; }
[ \t]                           ;
\/\/.*                          ;
\n                              { return END_OF_LINE; }
<<EOF>>                         { static int once = 0; return once++ ? 0 : END_OF_LINE; }

%%