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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ADDOP = 258,                   /* ADDOP  */
    MULOP = 259,                   /* MULOP  */
    INCOP = 260,                   /* INCOP  */
    RELOP = 261,                   /* RELOP  */
    ID = 262,                      /* ID  */
    CONST_INT = 263,               /* CONST_INT  */
    CONST_FLOAT = 264,             /* CONST_FLOAT  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    FOR = 267,                     /* FOR  */
    WHILE = 268,                   /* WHILE  */
    DO = 269,                      /* DO  */
    BREAK = 270,                   /* BREAK  */
    CHAR = 271,                    /* CHAR  */
    FLOAT = 272,                   /* FLOAT  */
    DOUBLE = 273,                  /* DOUBLE  */
    VOID = 274,                    /* VOID  */
    RETURN = 275,                  /* RETURN  */
    CONTINUE = 276,                /* CONTINUE  */
    PRINTLN = 277,                 /* PRINTLN  */
    ASSIGNOP = 278,                /* ASSIGNOP  */
    LOGICOP = 279,                 /* LOGICOP  */
    NOT = 280,                     /* NOT  */
    LPAREN = 281,                  /* LPAREN  */
    RPAREN = 282,                  /* RPAREN  */
    LCURL = 283,                   /* LCURL  */
    RCURL = 284,                   /* RCURL  */
    LSQUARE = 285,                 /* LSQUARE  */
    RSQUARE = 286,                 /* RSQUARE  */
    COMMA = 287,                   /* COMMA  */
    SEMICOLON = 288,               /* SEMICOLON  */
    DECOP = 289,                   /* DECOP  */
    INT = 290,                     /* INT  */
    SWITCH = 291,                  /* SWITCH  */
    CASE = 292,                    /* CASE  */
    DEFAULT = 293,                 /* DEFAULT  */
    BITOP = 294,                   /* BITOP  */
    CONST_CHAR = 295,              /* CONST_CHAR  */
    SINGLE_LINE_STRING = 296,      /* SINGLE_LINE_STRING  */
    MULTI_LINE_STRING = 297,       /* MULTI_LINE_STRING  */
    LOWER_THAN_ELSE = 298          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ADDOP 258
#define MULOP 259
#define INCOP 260
#define RELOP 261
#define ID 262
#define CONST_INT 263
#define CONST_FLOAT 264
#define IF 265
#define ELSE 266
#define FOR 267
#define WHILE 268
#define DO 269
#define BREAK 270
#define CHAR 271
#define FLOAT 272
#define DOUBLE 273
#define VOID 274
#define RETURN 275
#define CONTINUE 276
#define PRINTLN 277
#define ASSIGNOP 278
#define LOGICOP 279
#define NOT 280
#define LPAREN 281
#define RPAREN 282
#define LCURL 283
#define RCURL 284
#define LSQUARE 285
#define RSQUARE 286
#define COMMA 287
#define SEMICOLON 288
#define DECOP 289
#define INT 290
#define SWITCH 291
#define CASE 292
#define DEFAULT 293
#define BITOP 294
#define CONST_CHAR 295
#define SINGLE_LINE_STRING 296
#define MULTI_LINE_STRING 297
#define LOWER_THAN_ELSE 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 78 "1905095.y"

    SymbolInfo* symbol; 

#line 157 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
