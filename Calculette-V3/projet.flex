%option noyywrap
%{
#include <string>
#include "projet.bison.hpp" 
using namespace std;
%}
%%
[0-9]+(\.[0-9]*)?([Ee][0-9]+)?	{ yylval.valeur = atof(yytext); return NUMBER; }
Répéter|Réitérer { return REPEAT; }
un		{  yylval.valeur = 1; return NUMBER; }
deux	{  yylval.valeur = 2; return NUMBER; }
trois	{  yylval.valeur = 3; return NUMBER; }
plus	{  return '+'; }
fois	{  return '*'; }
[A-Za-z_][0-9A-Za-z_]*   { strcpy(yylval.nom,yytext); return IDENTIFIER; }
\n								{  return '\n'; }
\r								{  return '\n'; }
[ \t]							{ }
.								{  return yytext[0]; }
%%

