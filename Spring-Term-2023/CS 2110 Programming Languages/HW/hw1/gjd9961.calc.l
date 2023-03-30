%{
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "gjd9961.calc.tab.h" 
#include "MemoryMap.h"
%}

%option noyywrap
%%

                        /* 'val' in 'yylval.val' is the field declared in
                           calc2.y with the %union directive. */
[\n]                                         {return EOL;}
("PI")|("pi")                                {return PI;}
[0-9]+(\.[0-9]+)?                            { yylval.val = atoi(yytext); return NUMBER; }
"-"                                          { return SUB; }
"+"                                          { return ADD; }
"*"                                          { return MUL; }
"/"                                          { return DIV; }
"^"                                          { return POW; }
("%")|("MOD")|("mod")                        { return MOD; }
"("                                          { return LPAREN; }
")"                                          { return RPAREN; }
("sqrt")|("SQRT")                            { return SQRT; }
"!"                                          { return FACTORIAL; }
("abs")|("ABS")                              { return ABS; }
("floor")|("FLOOR")                          { return FLOOR; }
("CEIL")|("ceil")                            { return CEIL; }
("cos")|("COS")                              { return COS;}
("sin")|("SIN")                              { return SIN;}
("tan")|("TAN")                              { return TAN;}
("log2")|("LOG2")                            { return LOG2;}
("log10")|("LOG10")                          { return LOG10;}
("usd_to_euro")|("USD_TO_EURO")              {return USD_TO_EURO;}
("gbp_to_usd")|("GBP_TO_USD")                {return GBP_TO_USD;}
("usd_to_gbp")|("USD_TO_GBP")                {return USD_TO_GBP;}
("gbp_to_euro")|("GBP_TO_EURO")              {return GBP_TO_EURO;}
("EURO_TO_GBP")|("euro_to_gbp")              {return EURO_TO_GBP;}
("euro_to_usd")|("EURO_TO_USD")              {return EURO_TO_USD;}
("cel_to_fah")|("CEL_TO_FAH")                {return CEL_TO_FAH;}
("fah_to_cel")|("FAH_TO_CEL")                {return FAH_TO_CEL;}
("mi_to_km")|("MI_TO_KM")                    {return MI_TO_KM;}
("KM_TO_MI")|("km_to_mi")                    {return KM_TO_MI;}
("var")|("VAR")                              {return VAR_KEYWORD;}
[a-zA-Z0-9]+                                 {yylval.indexer = add_var(yytext); return VARIABLE; } // add index of variable to indexer, used in bison
"="                                          {return EQUALS;}
[ \t\r]+                                     { /* Ignore white characters. */ }
.                                            { std::cerr << "ERROR: Undefined Symbol" << std::endl; exit(1); }
%%
