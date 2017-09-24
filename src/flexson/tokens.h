/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SRC_FLEXSON_TOKENS_H_INCLUDED
# define YY_YY_SRC_FLEXSON_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/flexson/grammar.y" /* yacc.c:1909  */

	#include "../ast/ast.h"

#line 48 "src/flexson/tokens.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KW_INT = 258,
    KW_CHAR = 259,
    KW_VOID = 260,
    KW_FOR = 261,
    KW_WHILE = 262,
    KW_IF = 263,
    KW_ELSE = 264,
    KW_BREAK = 265,
    KW_CONTINUE = 266,
    KW_RETURN = 267,
    KW_SIZEOF = 268,
    KW_TIME = 269,
    OP_INCREMENT = 270,
    OP_DECREMENT = 271,
    OP_TIMESEQ = 272,
    OP_DIVEQ = 273,
    OP_MODEQ = 274,
    OP_ANDEQ = 275,
    OP_OREQ = 276,
    OP_XOREQ = 277,
    OP_SRLEQ = 278,
    OP_SLLEQ = 279,
    OP_PLUSEQ = 280,
    OP_MINUSEQ = 281,
    OP_EQ = 282,
    OP_NOTEQ = 283,
    OP_SRL = 284,
    OP_SLL = 285,
    OP_CAND = 286,
    OP_COR = 287,
    OP_GEQ = 288,
    OP_LEQ = 289,
    ID = 290,
    STRING_LIT = 291,
    DEC_INT = 292,
    HEX_INT = 293,
    OCT_INT = 294,
    CHAR_LIT = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 26 "src/flexson/grammar.y" /* yacc.c:1909  */

	CompilationUnit* c_unit;
	GlobalDeclaration* gdec_t;

	vector<Declaration*>* decl_ls;

	Declarator* declr_t;

	InitDeclarator* ideclr_t;
	vector<InitDeclarator*>* ideclr_ls;

	Initializer* inlzr_t;

	Parameter* par_t;
	vector<Parameter*>* par_ls;

	DataType dt;
	UnaryOp  uo;

	Expression* expr_t;
	vector<Expression*>* expr_ls;

	Statement* stmt_t;
	vector<Statement*>* stmt_ls;

	char* char_ptr;

#line 129 "src/flexson/tokens.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FLEXSON_TOKENS_H_INCLUDED  */
