/* A Bison parser, made by GNU Bison 3.8.2.  */

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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    INTEGER = 258,                 /* INTEGER  */
    STRING = 259,                  /* STRING  */
    REALCONST = 260,               /* REALCONST  */
    ID = 261,                      /* ID  */
    IF = 262,                      /* IF  */
    ELSE = 263,                    /* ELSE  */
    WHILE = 264,                   /* WHILE  */
    FOR = 265,                     /* FOR  */
    FUNCTION = 266,                /* FUNCTION  */
    RETURN = 267,                  /* RETURN  */
    BREAK = 268,                   /* BREAK  */
    CONTINUE = 269,                /* CONTINUE  */
    AND = 270,                     /* AND  */
    NOT = 271,                     /* NOT  */
    OR = 272,                      /* OR  */
    LOCAL = 273,                   /* LOCAL  */
    TRUE = 274,                    /* TRUE  */
    FALSE = 275,                   /* FALSE  */
    NIL = 276,                     /* NIL  */
    ASSIGN = 277,                  /* ASSIGN  */
    PLUS = 278,                    /* PLUS  */
    MINUS = 279,                   /* MINUS  */
    MUL = 280,                     /* MUL  */
    DIV = 281,                     /* DIV  */
    MOD = 282,                     /* MOD  */
    EQUAL = 283,                   /* EQUAL  */
    DIFF = 284,                    /* DIFF  */
    PLUS_PLUS = 285,               /* PLUS_PLUS  */
    MINUS_MINUS = 286,             /* MINUS_MINUS  */
    GREATER = 287,                 /* GREATER  */
    LESS = 288,                    /* LESS  */
    GREATER_EQUAL = 289,           /* GREATER_EQUAL  */
    LESS_EQUAL = 290,              /* LESS_EQUAL  */
    LEFT_BRACE = 291,              /* LEFT_BRACE  */
    RIGHT_BRACE = 292,             /* RIGHT_BRACE  */
    LEFT_BRACKET = 293,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 294,           /* RIGHT_BRACKET  */
    LEFT_PARENTHESIS = 295,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 296,       /* RIGHT_PARENTHESIS  */
    SEMICOLON = 297,               /* SEMICOLON  */
    COMMA = 298,                   /* COMMA  */
    COLON = 299,                   /* COLON  */
    D_COLON = 300,                 /* D_COLON  */
    DOT = 301,                     /* DOT  */
    D_DOT = 302,                   /* D_DOT  */
    UMINUS = 303                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INTEGER 258
#define STRING 259
#define REALCONST 260
#define ID 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define FUNCTION 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define AND 270
#define NOT 271
#define OR 272
#define LOCAL 273
#define TRUE 274
#define FALSE 275
#define NIL 276
#define ASSIGN 277
#define PLUS 278
#define MINUS 279
#define MUL 280
#define DIV 281
#define MOD 282
#define EQUAL 283
#define DIFF 284
#define PLUS_PLUS 285
#define MINUS_MINUS 286
#define GREATER 287
#define LESS 288
#define GREATER_EQUAL 289
#define LESS_EQUAL 290
#define LEFT_BRACE 291
#define RIGHT_BRACE 292
#define LEFT_BRACKET 293
#define RIGHT_BRACKET 294
#define LEFT_PARENTHESIS 295
#define RIGHT_PARENTHESIS 296
#define SEMICOLON 297
#define COMMA 298
#define COLON 299
#define D_COLON 300
#define DOT 301
#define D_DOT 302
#define UMINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "parser.y"

    int intVal;
    char* strVal;
    float floatVal;
    struct expr* expression;
    struct SymbolTableEntry *symTabEntry;
    struct stmt_t* stm;
    struct call* calls; 
    unsigned undef;   
    struct forloop* forloop;
    struct tablepair* tablepair;

#line 176 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
