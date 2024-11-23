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
     CLASS = 258,
     INHERITS = 259,
     IF = 260,
     THEN = 261,
     ELSE = 262,
     FI = 263,
     LET = 264,
     IN = 265,
     WHILE = 266,
     LOOP = 267,
     POOL = 268,
     CASE = 269,
     OF = 270,
     DARROW = 271,
     ESAC = 272,
     NEW = 273,
     ISVOID = 274,
     ASSIGN = 275,
     NOT = 276,
     LTE = 277,
     STRING = 278,
     TYPE = 279,
     ID = 280,
     INTEGER = 281,
     BOOLEAN = 282,
     TRUE = 283,
     FALSE = 284
   };
#endif
/* Tokens.  */
#define CLASS 258
#define INHERITS 259
#define IF 260
#define THEN 261
#define ELSE 262
#define FI 263
#define LET 264
#define IN 265
#define WHILE 266
#define LOOP 267
#define POOL 268
#define CASE 269
#define OF 270
#define DARROW 271
#define ESAC 272
#define NEW 273
#define ISVOID 274
#define ASSIGN 275
#define NOT 276
#define LTE 277
#define STRING 278
#define TYPE 279
#define ID 280
#define INTEGER 281
#define BOOLEAN 282
#define TRUE 283
#define FALSE 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 22 "cool.y"
{
    class_t *class;
    class_list_t *class_list;
    feature_list_t *feature_list;
    feature_t *feature;
    formal_list_t *formal_list;
    formal_t *formal;
    expr_t *expr;
    expr_list_t *expr_list;
    case_list_t *case_list;
    char *s;
    int i;
    bool b;
}
/* Line 1529 of yacc.c.  */
#line 122 "cool.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

