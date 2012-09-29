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
     ID_ = 258,
     ABRELLAVE_ = 259,
     CIERRALLAVE_ = 260,
     MENOR_ = 261,
     FACTOR_ = 262,
     MAYOR_ = 263,
     COMA_ = 264,
     FLOAT_ = 265,
     PUNTOCOMA_ = 266,
     COMILLAS_ = 267,
     CADENA_ = 268,
     LOCATION_ = 269,
     LOOKAT_ = 270,
     CAMERA_ = 271,
     AMBIENTAL_ = 272,
     COLOR_ = 273,
     PUNTUAL_ = 274,
     DIRECCIONAL_ = 275,
     FOCAL_ = 276,
     SPHERE_ = 277,
     PLANE_ = 278,
     CHECKER_ = 279,
     SIZE_ = 280,
     CUBE_ = 281,
     QUADRILATERAL_ = 282,
     TRIANGLE_ = 283,
     ESPECULAR_ = 284,
     DIFFUSE_ = 285,
     FOV_ = 286
   };
#endif
/* Tokens.  */
#define ID_ 258
#define ABRELLAVE_ 259
#define CIERRALLAVE_ 260
#define MENOR_ 261
#define FACTOR_ 262
#define MAYOR_ 263
#define COMA_ 264
#define FLOAT_ 265
#define PUNTOCOMA_ 266
#define COMILLAS_ 267
#define CADENA_ 268
#define LOCATION_ 269
#define LOOKAT_ 270
#define CAMERA_ 271
#define AMBIENTAL_ 272
#define COLOR_ 273
#define PUNTUAL_ 274
#define DIRECCIONAL_ 275
#define FOCAL_ 276
#define SPHERE_ 277
#define PLANE_ 278
#define CHECKER_ 279
#define SIZE_ 280
#define CUBE_ 281
#define QUADRILATERAL_ 282
#define TRIANGLE_ 283
#define ESPECULAR_ 284
#define DIFFUSE_ 285
#define FOV_ 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 32 "gramatica.y"
{
	char *cadena;
	float real;
	tPunto punto;
	tColor color;
	tChecker checker;
}
/* Line 1529 of yacc.c.  */
#line 119 "gramatica.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

