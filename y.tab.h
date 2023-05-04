
/*
 * lsting: Invariant Generation using Constraint Solving. 
 * Copyright (C) 2005 Sriram Sankaranarayanan < srirams@theory.stanford.edu>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     IDENT = 259,
     PRIME = 260,
     END = 261,
     VARIABLED = 262,
     LOCATION = 263,
     TRANSITION = 264,
     EQ = 265,
     LEQ = 266,
     GEQ = 267,
     LE = 268,
     GE = 269,
     PRES = 270,
     PROPS = 271,
     INVARIANT = 272,
     UMINUS = 273
   };
#endif
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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 92 "ltrtest.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 1248 of yacc.c.  */
#line 87 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



