%{
#include <iostream>
#include <math.h>
#include "util.h"
#include "gjd9961.calc.tab.h"
#include <string.h>

extern FILE* yyin;
extern double set_var(int, double);               // variable value setter
extern char *var_names[1028];                     // var names storage
extern double var_values[1028];                   // var values (double)
int yylex(); // A function that is to be generated and provided by flex,
             // which returns a next token when called repeatedly.
int yyerror(const char *p) { std::cerr << "ERROR: Undefined symbol " << p << std::endl; return 1; }
%}

%union {
    double val;
    int var_index;
    int indexer;
    /* You may include additional fields as you want. */
    /* char op; */
};

%start program_input
%type <val> line
%type <val> calculation
%type <val> constant
%type <val> expr
%type <val> function
%type <val> trig_function
%type <val> log_function
%type <val> conversion
%type <val> temp_conversion
%type <val> dist_conversion
%type <val> assignment

%token EOL PI
%token LPAREN RPAREN
%token ADD SUB MUL DIV POW MOD
%token SQRT FACTORIAL ABS FLOOR CEIL
%token COS SIN TAN
%token LOG2 LOG10
%token GBP_TO_USD USD_TO_GBP GBP_TO_EURO
%token EURO_TO_GBP USD_TO_EURO EURO_TO_USD
%token CEL_TO_FAH FAH_TO_CEL
%token MI_TO_KM KM_TO_MI
%token VAR_KEYWORD EQUALS
%token <indexer> VARIABLE

%token <val> NUMBER    /* 'val' is the (only) field declared in %union
                       which represents the type of the token. */



/* Resolve the ambiguity of the grammar by defining precedence. */

/* Order of directives will determine the precedence. */
%left SUB
%left ADD
%left MUL
%left DIV 
%left POW SQRT MOD /* left means left-associativity. */
%left LPAREN RPAREN


%%

// As given in the instructions

// Null or input + line
program_input : | 
    program_input line                             
     
// \n character or calculation followed by \n
line : EOL | calculation EOL { printf("=%.2f\n",$1); }

// Calculation is expression (1+2)*5 or assing var x = 5
calculation : expr | assignment 

// Simple
constant : PI                           {$$ = 3.14;}

// All the normal operations to be defined, including negative numbers
expr : SUB expr                         { $$ = -$2;}
     | NUMBER                              /* default action: { $$ = $1; } */
     | VARIABLE                         { $$ = var_values[$1]; } // maps index (VARIABLE) to value
     | constant
     | function
     | expr DIV expr                    { $$ = $1 / $3; }
     | expr MUL expr                    { $$ = $1 * $3; }
     | expr ADD expr                    { $$ = $1 + $3; }
     | expr SUB expr                    { $$ = $1 - $3; }
     | expr POW expr                    { $$ = pow($1, $3);}
     | expr MOD expr                    { $$ = modulo($1,$3);}
     | LPAREN expr RPAREN               { $$ = $2; }

// Functions in this order as given
function : conversion
     | log_function
     | trig_function
     | expr FACTORIAL                   {$$ = factorial($1);}
     | SQRT expr                        {$$ = sqrt($2);}
     | ABS expr                         {$$ = abs($2);}
     | FLOOR expr                       {$$ = floor($2);}
     | CEIL expr                        {$$ = ceil($2);}

trig_function : COS expr                {$$ = cos($2);}
     | SIN expr                         {$$ = sin($2);}
     | TAN expr                         {$$ = tan($2);}

log_function : LOG2 expr                {$$=log2($2);}
     | LOG10 expr                       {$$=log($2);}

// Call the util.h helper functions
conversion :  temp_conversion
     | dist_conversion
     | expr GBP_TO_USD                   {$$ = gbp_to_usd($1);}
     | expr USD_TO_GBP                   {$$ = usd_to_gbp($1);}
     | expr GBP_TO_EURO                  {$$ = gbp_to_euro($1);}
     | expr EURO_TO_GBP                  {$$ = euro_to_gbp($1);}
     | expr USD_TO_EURO                  {$$ = usd_to_euro($1);}
     | expr EURO_TO_USD                  {$$ = euro_to_usd($1);}

// Call the util.h helper functions
temp_conversion : expr CEL_TO_FAH       {$$=cel_to_fah($1);}
     | expr FAH_TO_CEL                  {$$=fah_to_cel($1);}

// Call the util.h helper functions
dist_conversion : expr MI_TO_KM         {$$ = m_to_km($1);}
     | expr KM_TO_MI                    {$$ = km_to_m($1);}

// Assignment: "var x = 5"
assignment : VAR_KEYWORD VARIABLE EQUALS calculation {$$ = set_var($2, $4);}
%%

int main(int argv, char** argc)
{
     std::string option, fname;
     printf("Enter `cli` for command line input parsing, `file` for file input parsing\n");
     std::cin >> option;
     
     if (option != "file" && option != "cli"){
          printf("Must enter either `file` or `cli`, you entered: %s\n", option.c_str());
          exit(-1);
     }

     if (option == "file"){
          std::cout << "File parsing selected, please enter a filename" << std::endl;
          std::cin >> fname;
          printf("Attempting to read from file: %s\n",fname.c_str());
          // Set yyin to look at file input
         yyin = fopen(fname.c_str(), "r");
         if (!yyin) {
			printf("ERROR: Can't open the file! %s\n", fname.c_str());
			exit(-1);
		}
		yyparse();
		
		printf("Done reading input from file %s\n", fname.c_str());
     }
     else {
         std::cout << "Command Line Input parsing selected, please enter any expression you like" << std::endl; 
         yyin = stdin;
         yyparse(); // A parsing function that will be generated by Bison.
     }
    
    return 0;
}
