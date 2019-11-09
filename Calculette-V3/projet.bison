%{
  #include <iostream>
  #include <map>
  #include <string>
  #include <vector>  
  using namespace std;
  extern FILE *yyin;
  extern int yylex ();
  int yyerror(char *s) { printf("%s\n", s); }

  map<string, double> variables;

  vector<pair<int,double>> instructions;

%}

%union
{
  double valeur;
  char nom[50];
}

%token <valeur> NUMBER
%token <nom> IDENTIFIER
%type <valeur> expression
%token REPEAT

%left '+' '-'     /* associativité à gauche */
%left '*' '/'     /* associativité à gauche */

%%
ligne : ligne instruction '\n' 
      |    /* Epsilon */
      ;
instruction : expression { }
            | REPEAT '(' expression ')' expression { for (int i =0; i<$3; i++) cout << $5 << endl;}
            | IDENTIFIER '=' expression  { variables[$1] = $3;
                         cout << "Affectation de " << $3 << " à " << $1 << endl;}
            |   /* Ligne vide*/
            ;
expression: expression '+' expression     { instructions.push_back(make_pair('+', 0));}
          | expression '-' expression     { instructions.push_back(make_pair('-', 0));}
          | expression '*' expression     { instructions.push_back(make_pair('*', 0));}
          | expression '/' expression     { instructions.push_back(make_pair('/', 0));}
          | '(' expression ')'            { }
          | NUMBER                        { instructions.push_back(make_pair(NUMBER, $1));}
          | IDENTIFIER                    { instructions.push_back(make_pair(IDENTIFIER, variables[$1]));}
          ;
%%

void print_program(){
  cout << "==== CODE GENERE ====" << endl;
  for (auto ins : instructions )
    cout << ins.first << "\t" << ins.second << endl;
  cout << "=====================" << endl;  
}


double depiler(vector<double> &pile) {
  double t = pile[pile.size()-1];
  cout << "Dépiler " << t << endl; 
  pile.pop_back();
  return t;
}


void run_program(){
  vector<double> pile; 
  double x,y;

  cout << "===== EXECUTION =====" << endl;
  for (auto ins : instructions ){   // A remplacer par un while car l'execution ne sera pas linéaire
    switch(ins.first){
      case '+':
        x = depiler(pile);
        y = depiler(pile);
        pile.push_back(y+x);
      break;
      case '*':
        x = depiler(pile);
        y = depiler(pile);
        pile.push_back(y*x);
      break;
      case NUMBER :
        pile.push_back(ins.second);
      break;
    }
  }
  cout << "Résultat : " << depiler(pile) << endl;
  cout << "=====================" << endl;  
}

int main(int argc, char **argv) {
  
  if ( argc > 1 )
    yyin = fopen( argv[1], "r" );
  else
    yyin = stdin;
  yyparse();

  print_program();

  run_program();

}