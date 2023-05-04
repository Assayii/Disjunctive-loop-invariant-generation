/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LTRTEST_TAB_H_INCLUDED
# define YY_YY_LTRTEST_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    IDENT = 259,                   /* IDENT  */
    PRIME = 260,                   /* PRIME  */
    END = 261,                     /* END  */
    VARIABLED = 262,               /* VARIABLED  */
    LOCATION = 263,                /* LOCATION  */
    TRANSITION = 264,              /* TRANSITION  */
    EQ = 265,                      /* EQ  */
    LEQ = 266,                     /* LEQ  */
    GEQ = 267,                     /* GEQ  */
    LE = 268,                      /* LE  */
    GE = 269,                      /* GE  */
    PRES = 270,                    /* PRES  */
    PROPS = 271,                   /* PROPS  */
    INVARIANT = 272,               /* INVARIANT  */
    UMINUS = 273                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT 258
#define IDENT 259
#define PRIME 260
#define END 261
#define VARIABLED 262
#define LOCATION 263
#define TRANSITION 264
#define EQ 265
#define LEQ 266
#define GEQ 267
#define LE 268
#define GE 269
#define PRES 270
#define PROPS 271
#define INVARIANT 272
#define UMINUS 273

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 92 "ltrtest.y"

   char * string;
   var_info * v;
   int dummy;
   int integer;
   char identifier[MAX_ID_SIZE];
   var_info * vi;
   Location *ll;
   TransitionRelation * tt;
   Linear_Expression * li;
   Constraint * cc;
   C_Polyhedron * pp;
   vector<int> * vv;

#line 118 "ltrtest.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LTRTEST_TAB_H_INCLUDED  */
