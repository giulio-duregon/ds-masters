/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EOL = 258,
     PI = 259,
     LPAREN = 260,
     RPAREN = 261,
     ADD = 262,
     SUB = 263,
     MUL = 264,
     DIV = 265,
     POW = 266,
     MOD = 267,
     SQRT = 268,
     FACTORIAL = 269,
     ABS = 270,
     FLOOR = 271,
     CEIL = 272,
     COS = 273,
     SIN = 274,
     TAN = 275,
     LOG2 = 276,
     LOG10 = 277,
     GBP_TO_USD = 278,
     USD_TO_GBP = 279,
     GBP_TO_EURO = 280,
     EURO_TO_GBP = 281,
     USD_TO_EURO = 282,
     EURO_TO_USD = 283,
     CEL_TO_FAH = 284,
     FAH_TO_CEL = 285,
     MI_TO_KM = 286,
     KM_TO_MI = 287,
     VAR_KEYWORD = 288,
     EQUALS = 289,
     VARIABLE = 290,
     NUMBER = 291
   };
#endif
/* Tokens.  */
#define EOL 258
#define PI 259
#define LPAREN 260
#define RPAREN 261
#define ADD 262
#define SUB 263
#define MUL 264
#define DIV 265
#define POW 266
#define MOD 267
#define SQRT 268
#define FACTORIAL 269
#define ABS 270
#define FLOOR 271
#define CEIL 272
#define COS 273
#define SIN 274
#define TAN 275
#define LOG2 276
#define LOG10 277
#define GBP_TO_USD 278
#define USD_TO_GBP 279
#define GBP_TO_EURO 280
#define EURO_TO_GBP 281
#define USD_TO_EURO 282
#define EURO_TO_USD 283
#define CEL_TO_FAH 284
#define FAH_TO_CEL 285
#define MI_TO_KM 286
#define KM_TO_MI 287
#define VAR_KEYWORD 288
#define EQUALS 289
#define VARIABLE 290
#define NUMBER 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "gjd9961.calc.y"
{
    double val;
    int var_index;
    int indexer;
    /* You may include additional fields as you want. */
    /* char op; */
}
/* Line 1529 of yacc.c.  */
#line 129 "gjd9961.calc.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

