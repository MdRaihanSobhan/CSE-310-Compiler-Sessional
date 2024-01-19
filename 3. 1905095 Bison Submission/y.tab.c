/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "1905095.y"

#include<iostream>
#include<stdio.h>
#include<cstring>
#include <set>
#include "1905095.cpp" 
#define ll long long int
#include <sstream>
#include <stdlib.h>

int yyparse(void);
void yyerror(char *s){
	printf("%s\n",s);
}

int yylex(void);

ofstream log_out; 
ofstream error_out;
ofstream parse_out;

extern FILE *yyin; 
SymbolTable* symbolTable = new SymbolTable(11);

extern ll lines; 
ll errors = 0;


string curr_type = "void";
string running_function = "global";
string curr_call = "global";
vector<SymbolInfo> parameter_list;

void showRule(string ruleName){
    log_out<<ruleName<<endl;
}

string st= "";
vector<int> debug; 
string debugString =" "; 
string debugGetType=" "; 

string showParseLine(SymbolInfo* nodeSymbol){
    string rule = nodeSymbol->getType()+ ":     ";
    for(int i=0; i<nodeSymbol->child_list.size(); i++){
        rule+=nodeSymbol->child_list[i]->getType()+" ";
    }
    rule+="<Line: "+to_string(nodeSymbol->getStartLine())+"-"+to_string(nodeSymbol->getEndLine())+">\n";
    return rule; 
}


void showParseTree(SymbolInfo* nodeSymbol, int spaceNo){
    for(int i=0;i<spaceNo;i++){
        parse_out<<" "; 
    }
    parse_out<< showParseLine(nodeSymbol); 
    for(int i=0; i<nodeSymbol->getChild_List().size(); i++){
        if(nodeSymbol->child_list[i]->getLeaf()){
            showParseLine(nodeSymbol->child_list[i]); 
            for(int i=0;i<spaceNo;i++){
                parse_out<<" "; 
            }
            parse_out<<nodeSymbol->child_list[i]->getType()<<": "<<nodeSymbol->child_list[i]->getName()<<"  <Line: "<<to_string(nodeSymbol->child_list[i]->getStartLine())<<">"<<endl;
        }
        else{ 
            showParseTree(nodeSymbol->child_list[i],spaceNo+1); 
        }
    }
    if(nodeSymbol->getLeaf()){
        return;
    }    
}



#line 148 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 291 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ADDOP = 3,                      /* ADDOP  */
  YYSYMBOL_MULOP = 4,                      /* MULOP  */
  YYSYMBOL_INCOP = 5,                      /* INCOP  */
  YYSYMBOL_RELOP = 6,                      /* RELOP  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_CONST_INT = 8,                  /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 9,                /* CONST_FLOAT  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_BREAK = 15,                     /* BREAK  */
  YYSYMBOL_CHAR = 16,                      /* CHAR  */
  YYSYMBOL_FLOAT = 17,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 18,                    /* DOUBLE  */
  YYSYMBOL_VOID = 19,                      /* VOID  */
  YYSYMBOL_RETURN = 20,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 21,                  /* CONTINUE  */
  YYSYMBOL_PRINTLN = 22,                   /* PRINTLN  */
  YYSYMBOL_ASSIGNOP = 23,                  /* ASSIGNOP  */
  YYSYMBOL_LOGICOP = 24,                   /* LOGICOP  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_LPAREN = 26,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 27,                    /* RPAREN  */
  YYSYMBOL_LCURL = 28,                     /* LCURL  */
  YYSYMBOL_RCURL = 29,                     /* RCURL  */
  YYSYMBOL_LSQUARE = 30,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 31,                   /* RSQUARE  */
  YYSYMBOL_COMMA = 32,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 33,                 /* SEMICOLON  */
  YYSYMBOL_DECOP = 34,                     /* DECOP  */
  YYSYMBOL_INT = 35,                       /* INT  */
  YYSYMBOL_SWITCH = 36,                    /* SWITCH  */
  YYSYMBOL_CASE = 37,                      /* CASE  */
  YYSYMBOL_DEFAULT = 38,                   /* DEFAULT  */
  YYSYMBOL_BITOP = 39,                     /* BITOP  */
  YYSYMBOL_CONST_CHAR = 40,                /* CONST_CHAR  */
  YYSYMBOL_SINGLE_LINE_STRING = 41,        /* SINGLE_LINE_STRING  */
  YYSYMBOL_MULTI_LINE_STRING = 42,         /* MULTI_LINE_STRING  */
  YYSYMBOL_LOWER_THAN_ELSE = 43,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_start = 45,                     /* start  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_unit = 47,                      /* unit  */
  YYSYMBOL_func_declaration = 48,          /* func_declaration  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_func_definition = 51,           /* func_definition  */
  YYSYMBOL_52_3 = 52,                      /* $@3  */
  YYSYMBOL_53_4 = 53,                      /* $@4  */
  YYSYMBOL_parameter_list = 54,            /* parameter_list  */
  YYSYMBOL_compound_statement = 55,        /* compound_statement  */
  YYSYMBOL_56_5 = 56,                      /* $@5  */
  YYSYMBOL_57_6 = 57,                      /* $@6  */
  YYSYMBOL_var_declaration = 58,           /* var_declaration  */
  YYSYMBOL_type_specifier = 59,            /* type_specifier  */
  YYSYMBOL_declaration_list = 60,          /* declaration_list  */
  YYSYMBOL_statements = 61,                /* statements  */
  YYSYMBOL_statement = 62,                 /* statement  */
  YYSYMBOL_expression_statement = 63,      /* expression_statement  */
  YYSYMBOL_variable = 64,                  /* variable  */
  YYSYMBOL_expression = 65,                /* expression  */
  YYSYMBOL_logic_expression = 66,          /* logic_expression  */
  YYSYMBOL_rel_expression = 67,            /* rel_expression  */
  YYSYMBOL_simple_expression = 68,         /* simple_expression  */
  YYSYMBOL_term = 69,                      /* term  */
  YYSYMBOL_unary_expression = 70,          /* unary_expression  */
  YYSYMBOL_factor = 71,                    /* factor  */
  YYSYMBOL_72_7 = 72,                      /* $@7  */
  YYSYMBOL_argument_list = 73,             /* argument_list  */
  YYSYMBOL_arguments = 74                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   150

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  127

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,   104,   114,   125,   137,   145,   156,   156,
     190,   190,   218,   218,   270,   270,   305,   332,   348,   363,
     378,   378,   400,   400,   423,   441,   451,   461,   472,   502,
     530,   555,   583,   591,   602,   610,   618,   626,   641,   653,
     668,   680,   698,   710,   715,   726,   765,   803,   814,   836,
     846,   864,   874,   892,   902,   925,   936,   975,   985,   995,
    1008,  1019,  1019,  1082,  1094,  1105,  1116,  1126,  1138,  1152,
    1158,  1171
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ADDOP", "MULOP",
  "INCOP", "RELOP", "ID", "CONST_INT", "CONST_FLOAT", "IF", "ELSE", "FOR",
  "WHILE", "DO", "BREAK", "CHAR", "FLOAT", "DOUBLE", "VOID", "RETURN",
  "CONTINUE", "PRINTLN", "ASSIGNOP", "LOGICOP", "NOT", "LPAREN", "RPAREN",
  "LCURL", "RCURL", "LSQUARE", "RSQUARE", "COMMA", "SEMICOLON", "DECOP",
  "INT", "SWITCH", "CASE", "DEFAULT", "BITOP", "CONST_CHAR",
  "SINGLE_LINE_STRING", "MULTI_LINE_STRING", "LOWER_THAN_ELSE", "$accept",
  "start", "program", "unit", "func_declaration", "$@1", "$@2",
  "func_definition", "$@3", "$@4", "parameter_list", "compound_statement",
  "$@5", "$@6", "var_declaration", "type_specifier", "declaration_list",
  "statements", "statement", "expression_statement", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "$@7", "argument_list",
  "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-81)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-23)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,   -81,   -81,   -81,    10,    -2,   -81,   -81,   -81,   -81,
      33,   -81,   -81,    24,    11,     3,    13,    50,   -81,    30,
     -16,    52,    31,    35,    34,    38,    42,    -2,   -81,   -81,
      55,   -81,    48,   -81,    47,    38,    74,    51,    95,    58,
     -81,   -81,   -81,   -81,   124,    26,   -81,   -81,    63,    64,
      67,   124,    70,   124,   124,   -81,   -81,   -81,    77,    66,
     -81,   -81,     0,    73,   -81,    76,    25,    93,   -81,   -81,
     -81,     2,   -81,   -81,   124,   124,   124,   124,    78,   102,
     -81,    83,    86,   -81,   -81,   -81,   124,   -81,   -81,   124,
     124,   124,   124,   124,    82,    91,    95,    92,   -81,    97,
     -81,   -81,   -81,    93,   119,   -81,   -81,    98,    94,   -81,
      95,   124,    95,    96,   -81,   124,   123,    95,   -81,   -81,
     -81,    95,   124,   -81,   108,    95,   -81
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    26,    27,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    30,     0,     0,     0,     0,    24,    10,
       0,    19,     0,    28,     0,     0,     8,     0,    18,    31,
       0,    11,    20,    15,     0,     0,    17,     0,     0,     0,
       9,    13,    16,    29,     0,    45,    64,    65,     0,     0,
       0,     0,     0,     0,     0,    43,    36,    34,     0,     0,
      32,    35,    60,     0,    47,    49,    51,    53,    55,    59,
      23,    60,    57,    61,     0,     0,     0,     0,     0,     0,
      58,     0,    30,    21,    33,    66,     0,    67,    44,     0,
       0,     0,     0,    69,     0,     0,     0,     0,    42,     0,
      63,    48,    50,    54,    52,    56,    71,     0,    68,    46,
       0,     0,     0,     0,    62,     0,    38,     0,    40,    41,
      70,     0,     0,    39,     0,     0,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -81,   -81,   -81,   131,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -17,   -81,   -81,    32,    14,   -81,   -81,   -57,   -81,
     -44,   -50,   -80,    49,    46,    53,   -41,   -81,   -81,   -81,
     -81
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    34,    24,     8,    35,    25,
      20,    56,    38,    39,    57,    58,    14,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    93,   107,
     108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      71,    78,    84,    72,    81,    85,   101,    85,    33,    71,
      11,    26,    80,   106,    10,     1,    27,     2,    41,    10,
       1,    22,     2,    86,    94,    95,    96,    97,    90,    21,
      19,    91,     9,     3,    87,   120,    87,     9,     3,   111,
      13,    36,    71,    17,    18,    71,    71,    71,    71,    71,
      15,   105,    73,   116,    16,   118,    74,    23,   -14,    28,
     122,   117,    29,    37,   123,    30,    32,    31,   126,    44,
     -12,    71,   124,    45,    46,    47,    48,   -22,    49,    50,
      40,    42,    43,     1,    82,     2,    51,    70,    52,    75,
      76,    53,    54,    77,    32,    83,    79,    92,    44,    55,
      89,     3,    45,    46,    47,    48,    88,    49,    50,    99,
     100,    98,     1,   109,     2,    51,    16,    52,   110,   112,
      53,    54,    90,    32,   113,   114,   115,    44,    55,   119,
       3,    45,    46,    47,   121,   125,    12,   104,   102,     0,
       0,     0,     0,   103,     0,     0,     0,     0,     0,    53,
      54
};

static const yytype_int8 yycheck[] =
{
      44,    51,    59,    44,    54,     5,    86,     5,    25,    53,
       0,    27,    53,    93,     0,    17,    32,    19,    35,     5,
      17,     8,    19,    23,    74,    75,    76,    77,     3,    15,
      27,     6,     0,    35,    34,   115,    34,     5,    35,    96,
       7,    27,    86,    32,    33,    89,    90,    91,    92,    93,
      26,    92,    26,   110,    30,   112,    30,     7,    28,     7,
     117,   111,    31,     8,   121,    30,    28,    33,   125,     3,
      28,   115,   122,     7,     8,     9,    10,    29,    12,    13,
      33,     7,    31,    17,     7,    19,    20,    29,    22,    26,
      26,    25,    26,    26,    28,    29,    26,     4,     3,    33,
      24,    35,     7,     8,     9,    10,    33,    12,    13,     7,
      27,    33,    17,    31,    19,    20,    30,    22,    27,    27,
      25,    26,     3,    28,    27,    27,    32,     3,    33,    33,
      35,     7,     8,     9,    11,    27,     5,    91,    89,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    25,
      26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    17,    19,    35,    45,    46,    47,    48,    51,    58,
      59,     0,    47,     7,    60,    26,    30,    32,    33,    27,
      54,    59,     8,     7,    50,    53,    27,    32,     7,    31,
      30,    33,    28,    55,    49,    52,    59,     8,    56,    57,
      33,    55,     7,    31,     3,     7,     8,     9,    10,    12,
      13,    20,    22,    25,    26,    33,    55,    58,    59,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      29,    64,    70,    26,    30,    26,    26,    26,    65,    26,
      70,    65,     7,    29,    62,     5,    23,    34,    33,    24,
       3,     6,     4,    72,    65,    65,    65,    65,    33,     7,
      27,    66,    67,    69,    68,    70,    66,    73,    74,    31,
      27,    62,    27,    27,    27,    32,    62,    65,    62,    33,
      66,    11,    62,    62,    65,    27,    62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    47,    49,    48,
      50,    48,    52,    51,    53,    51,    54,    54,    54,    54,
      56,    55,    57,    55,    58,    59,    59,    59,    60,    60,
      60,    60,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    65,    65,    66,
      66,    67,    67,    68,    68,    69,    69,    70,    70,    70,
      71,    72,    71,    71,    71,    71,    71,    71,    73,    73,
      74,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     0,     7,
       0,     6,     0,     7,     0,     6,     4,     3,     2,     1,
       0,     4,     0,     3,     3,     1,     1,     1,     3,     6,
       1,     4,     1,     2,     1,     1,     1,     9,     5,     7,
       5,     5,     3,     1,     2,     1,     4,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     2,     2,     1,
       1,     0,     5,     3,     1,     1,     2,     2,     1,     0,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 91 "1905095.y"
        {
		(yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"start");
        debugString+=(yyvsp[0].symbol)->getName(); 
		showRule("start : program");
		log_out<<"Total lines: "<<lines<<endl;
		log_out<<"Total errors: "<<errors<<endl;
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine()); 
        showParseTree((yyval.symbol),0);
	}
#line 1449 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 105 "1905095.y"
    {
        showRule("program : program unit");
        (yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"program");
        debugString+=(yyvsp[-1].symbol)->getName(); 
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine()); 
	}
#line 1463 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 115 "1905095.y"
    {
        showRule("program : unit");
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"program");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine()); 
	}
#line 1475 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 126 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"unit");
        showRule("unit : var_declaration");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        debugString+=(yyvsp[0].symbol)->getName(); 
        debugGetType+=(yyvsp[0].symbol)->getType(); 

	}
#line 1490 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 138 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"unit");
		showRule("unit : func_declaration");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
	}
#line 1502 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 146 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"unit");
		showRule("unit : func_definition");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
    }
#line 1514 "y.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 156 "1905095.y"
                                                                   {
		running_function = (yyvsp[-3].symbol)->getName();
        debugString+=(yyvsp[-4].symbol)->getName(); 
		if(symbolTable->lookUp(running_function) == NULL){
			SymbolInfo* temp = new SymbolInfo(running_function, (yyvsp[-4].symbol)->getName());
			for(auto i : parameter_list){
				temp->addParameter(i);
			}
			temp->setData_type((yyvsp[-4].symbol)->getName());
			temp->setStructure_type("func");
            temp->setType((yyvsp[-4].symbol)->getType()); 
			parameter_list.clear();
			symbolTable->Insert(*temp);
		}
		else{
            error_out<<"Line# "<<lines<<": Redefinition of '"+running_function<<"'"<<endl; 
            errors++; 			
		}
        running_function = (yyvsp[-3].symbol)->getName();

	}
#line 1540 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN $@1 SEMICOLON  */
#line 176 "1905095.y"
                        {
        showRule("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
        string symName = (yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[0].symbol)->getName()+"\n";
        (yyval.symbol) = new SymbolInfo(symName, "func_declaration");
        (yyval.symbol)->addChild((yyvsp[-6].symbol));
        (yyval.symbol)->addChild((yyvsp[-5].symbol));
        (yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-6].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
	}
#line 1558 "y.tab.c"
    break;

  case 10: /* $@2: %empty  */
#line 190 "1905095.y"
                                        {
			running_function=(yyvsp[-2].symbol)->getName();
			if(symbolTable->lookUp(running_function) == NULL){
				SymbolInfo* temp = new SymbolInfo(running_function, (yyvsp[-3].symbol)->getType());
                debugGetType+=(yyvsp[-3].symbol)->getType(); 
				temp->setStructure_type("func");
				temp->setData_type((yyvsp[-3].symbol)->getName());
				symbolTable->Insert(*temp);
			}
			else{
                error_out<<"Line# "<<lines<<": Redeclaration of "+running_function<<endl; 
                errors++;				
			}
		}
#line 1577 "y.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN RPAREN $@2 SEMICOLON  */
#line 203 "1905095.y"
                                {
            showRule("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
            string symName = (yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[0].symbol)->getName()+"\n";
            (yyval.symbol) = new SymbolInfo(symName, "func_declaration");
            (yyval.symbol)->addChild((yyvsp[-5].symbol));
            (yyval.symbol)->addChild((yyvsp[-4].symbol));
            (yyval.symbol)->addChild((yyvsp[-3].symbol));
            (yyval.symbol)->addChild((yyvsp[-2].symbol));
            (yyval.symbol)->addChild((yyvsp[0].symbol));
            (yyval.symbol)->setStartLine((yyvsp[-5].symbol)->getStartLine()); 
            (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		}
#line 1594 "y.tab.c"
    break;

  case 12: /* $@3: %empty  */
#line 218 "1905095.y"
                                                                {
	running_function=(yyvsp[-3].symbol)->getName();
    debugString+=(yyvsp[-4].symbol)->getName(); 
    debugGetType+=(yyvsp[-4].symbol)->getType(); 
	if(symbolTable->lookUp(running_function) == NULL){
		SymbolInfo* temp = new SymbolInfo(running_function, "ID");
		for(auto i : parameter_list){
			temp->addParameter(i);
		}
		temp->setStructure_type("func");
		temp->setData_type((yyvsp[-4].symbol)->getName());
		symbolTable->Insert(*temp);
	}
	else{
		SymbolInfo* temp = symbolTable->lookUp(running_function);
		
		if(temp->getStructure_type() == "func"){
            error_out<<"Line# "<<lines<<": Redeclaration of "+running_function<<endl; 
            errors++;
		}
		else{
			vector<SymbolInfo> vec_temp = temp->getParameterList();
			if((yyvsp[-4].symbol)->getName() != temp->getData_type()){
                error_out<<"Line# "<<lines<<": Return type mismatch in function "+temp->getName()<<endl;
                errors++;				
			}
			if(vec_temp.size()> parameter_list.size()){
                error_out<<"Line# "<<lines<<": Too many arguments to function "<<running_function<<endl;
                errors++;
			}
            else if(vec_temp.size()< parameter_list.size()){
                error_out<<"Line# "<<lines<<": Too few arguments to function "<<running_function<<endl;
                errors++;
            }
		}
	}
	
}
#line 1637 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@3 compound_statement  */
#line 255 "1905095.y"
                        {

    showRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
    string symName = (yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[0].symbol)->getName();
    debugString+=(yyvsp[-6].symbol)->getName(); 
    (yyval.symbol) = new SymbolInfo(symName, "func");	
    (yyval.symbol)->addChild((yyvsp[-6].symbol));
    (yyval.symbol)->addChild((yyvsp[-5].symbol));
    (yyval.symbol)->addChild((yyvsp[-4].symbol));
    (yyval.symbol)->addChild((yyvsp[-3].symbol));
    (yyval.symbol)->addChild((yyvsp[-2].symbol));
    (yyval.symbol)->addChild((yyvsp[0].symbol));
    (yyval.symbol)->setStartLine((yyvsp[-6].symbol)->getStartLine()); 
    (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
    }
#line 1657 "y.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 270 "1905095.y"
                                      {
        running_function=(yyvsp[-2].symbol)->getName();
        if(symbolTable->lookUp(running_function) == NULL){
            SymbolInfo* temp = new SymbolInfo(running_function, (yyvsp[-3].symbol)->getType());
            
            temp->setStructure_type("func");
            temp->setData_type((yyvsp[-3].symbol)->getName());
            symbolTable->Insert(*temp);
        }
        else{
            SymbolInfo* temp = symbolTable->lookUp(running_function);
            if(temp->getStructure_type() == "func_dec"){
                error_out<<"Line# "<<lines<<":  Redeclaration of function "+running_function<<endl; 
                errors++;	
            }
        }
        running_function = (yyvsp[-2].symbol)->getName();

			
	}
#line 1682 "y.tab.c"
    break;

  case 15: /* func_definition: type_specifier ID LPAREN RPAREN $@4 compound_statement  */
#line 289 "1905095.y"
                                {
        showRule("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
        string symName = (yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[0].symbol)->getName();
        (yyval.symbol) = new SymbolInfo(symName, "func_definition");
        (yyval.symbol)->addChild((yyvsp[-5].symbol));
        (yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-5].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
	}
#line 1699 "y.tab.c"
    break;

  case 16: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 306 "1905095.y"
    {
        showRule("parameter_list  : parameter_list COMMA type_specifier ID");
		(yyval.symbol)=new SymbolInfo((yyvsp[-3].symbol)->getName()+(yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"parameter_list");
		(yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-3].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        SymbolInfo* temp = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
        temp->setStructure_type("var");
        temp->setData_type((yyvsp[-1].symbol)->getName());
        bool gotten = false;
        for(auto i: parameter_list){
            if(i.getName() == temp->getName()){
                error_out<<"Line# "<<lines<<":  Redeclaration of parameter '"+i.getName()<<"'"<<endl; 
                errors++;
                gotten = true;
                break;
            }
        }
        if(gotten == false){
            parameter_list.push_back(*temp);
        }
    }
#line 1730 "y.tab.c"
    break;

  case 17: /* parameter_list: parameter_list COMMA type_specifier  */
#line 333 "1905095.y"
    {
        showRule("parameter_list  : parameter_list COMMA type_specifier");
        string symName = (yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName();

        (yyval.symbol) = new SymbolInfo(symName, "parameter_list");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        SymbolInfo* temp = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
        temp->setStructure_type("var");
        temp->setData_type((yyvsp[0].symbol)->getName());
        parameter_list.push_back(*temp);
    }
#line 1750 "y.tab.c"
    break;

  case 18: /* parameter_list: type_specifier ID  */
#line 349 "1905095.y"
    {
        showRule("parameter_list  : type_specifier ID");
        string symName = (yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName();

        (yyval.symbol) = new SymbolInfo(symName, "type_specifier");
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        SymbolInfo* temp = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
        temp->setStructure_type("var");
        temp->setStructure_type((yyvsp[-1].symbol)->getName());
        parameter_list.push_back(*temp);
    }
#line 1769 "y.tab.c"
    break;

  case 19: /* parameter_list: type_specifier  */
#line 364 "1905095.y"
    {
        showRule("parameter_list  : type_specifier");
        string symName = (yyvsp[0].symbol)->getName();
        (yyval.symbol) = new SymbolInfo(symName, "parameter_list");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        SymbolInfo* temp = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
        temp->setStructure_type("var");
        temp->setData_type((yyvsp[0].symbol)->getName());
        parameter_list.push_back(*temp);
    }
#line 1786 "y.tab.c"
    break;

  case 20: /* $@5: %empty  */
#line 378 "1905095.y"
                              { 
        symbolTable->enter_scope(); 
        if(parameter_list.size() != 0){
            for(auto i : parameter_list){
                symbolTable->Insert(i);
            }
        }
        parameter_list.clear();
    
    }
#line 1801 "y.tab.c"
    break;

  case 21: /* compound_statement: LCURL $@5 statements RCURL  */
#line 388 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-3].symbol)->getName()+"\n"+(yyvsp[-1].symbol)->getName()+"\n"+(yyvsp[0].symbol)->getName()+"\n","compound_statement");
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-3].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

		showRule("compound_statement:   LCURL statements RCURL");
        symbolTable->print_all_scopes(log_out);
        symbolTable->exit_scope(); 
    }
#line 1818 "y.tab.c"
    break;

  case 22: /* $@6: %empty  */
#line 400 "1905095.y"
              {
        symbolTable->enter_scope(); 
        
        if(parameter_list.size() != 0){
            for(auto i : parameter_list){
                symbolTable->Insert(i);
            }
        }
        parameter_list.clear();
    }
#line 1833 "y.tab.c"
    break;

  case 23: /* compound_statement: LCURL $@6 RCURL  */
#line 410 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[0].symbol)->getName(),"compound_statement");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		showRule("compound_statement:   LCURL RCURL");
        symbolTable->exit_scope(); 
        symbolTable->print_all_scopes(log_out); 

    }
#line 1849 "y.tab.c"
    break;

  case 24: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 424 "1905095.y"
    {
    	(yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"var_declaration");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		showRule("var_declaration : type_specifier declaration_list SEMICOLON");
        if((yyvsp[-2].symbol)->getName() == "void"){
            error_out<<"Line# "<<lines<<": Variable or field '"<<(yyvsp[-2].symbol)->getName()<<"' declared void"<<endl; 
            errors++;
		}
	}
#line 1867 "y.tab.c"
    break;

  case 25: /* type_specifier: INT  */
#line 442 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"type_specifier");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        debugString+=(yyvsp[0].symbol)->getName(); 
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		showRule("type_specifier	: INT");
        curr_type="int"; 
	}
#line 1881 "y.tab.c"
    break;

  case 26: /* type_specifier: FLOAT  */
#line 452 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"type_specifier");
        (yyval.symbol)->addChild((yyvsp[0].symbol)); 
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
    	showRule("type_specifier	: FLOAT");
        curr_type= "float"; 
				
	}
#line 1895 "y.tab.c"
    break;

  case 27: /* type_specifier: VOID  */
#line 462 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"type_specifier");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		showRule("type_specifier	: VOID");
        curr_type="void"; 
	}
#line 1908 "y.tab.c"
    break;

  case 28: /* declaration_list: declaration_list COMMA ID  */
#line 473 "1905095.y"
    {
		showRule("declaration_list : declaration_list COMMA ID");
		(yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"declaration_list");

        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
                
        SymbolInfo* temp = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
        temp->setStructure_type("var");
        temp->setData_type(curr_type); 

        ScopeTable* forErrorCheck = symbolTable->getCurrent_scope();
                        
        SymbolInfo* toInsert =  forErrorCheck->lookUp(temp->getName());

        if(toInsert!=NULL){
            error_out<<"Line# "<<lines<<": Redeclaration of "+ temp->getName()<<endl; 
            errors++;
        }

        if(curr_type!="void"){
            symbolTable->Insert(*temp);
        }
		
	}
#line 1941 "y.tab.c"
    break;

  case 29: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 503 "1905095.y"
    {
		showRule("declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
        (yyval.symbol)=new SymbolInfo((yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"declaration_list");
        
        (yyval.symbol)->addChild((yyvsp[-5].symbol));
        (yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-5].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        SymbolInfo* temp = new SymbolInfo((yyvsp[-3].symbol)->getName(), (yyvsp[-3].symbol)->getType());
        temp->setStructure_type("array");
        temp->setData_type(curr_type);

        ScopeTable* forErrorCheck = symbolTable->getCurrent_scope();
        if(forErrorCheck->lookUp(temp->getName())!=NULL){
            error_out<<"Line# "<<lines<<": Redeclaration of "+ temp->getName()<<endl; 
            errors++;
        }
        if(curr_type != "void"){
            symbolTable->Insert(*temp);
        }
						
	}
#line 1972 "y.tab.c"
    break;

  case 30: /* declaration_list: ID  */
#line 531 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"declaration_list");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		showRule("declaration_list : ID");
        debugGetType+=(yyvsp[0].symbol)->getType(); 
        // parse_out<<debugGetType<<endl; 

        SymbolInfo* temp = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
        temp->setStructure_type("var");
        temp->setData_type(curr_type);

        ScopeTable* forErrorCheck = symbolTable->getCurrent_scope();
        if(symbolTable->lookUpCurrentScope(temp->getName())!=NULL){
            error_out<<"Line# "<<lines<<": Redeclaration of "+ temp->getName()<<endl; 
            errors++;
        }
        if(curr_type != "void"){
            symbolTable->Insert(*temp);
        }
        
				
	}
#line 2001 "y.tab.c"
    break;

  case 31: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 556 "1905095.y"
    {
    	(yyval.symbol)=new SymbolInfo((yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"declaration_list");
		(yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-3].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        debugString+=(yyvsp[-3].symbol)->getName(); 
        showRule("declaration_list : ID LSQUARE CONST_INT RSQUARE");
        SymbolInfo* temp = new SymbolInfo((yyvsp[-3].symbol)->getName(), (yyvsp[-3].symbol)->getType());
        temp->setStructure_type("array");
        temp->setData_type(curr_type);
        
        ScopeTable* forErrorCheck = symbolTable->getCurrent_scope();
        if(forErrorCheck->lookUp(temp->getName())!=NULL){
            
        error_out<<"Line# "<<lines<<": Redeclaration of "+ temp->getName()<<endl; 
        errors++;        
        }					
        if(curr_type != "void"){
            symbolTable->Insert(*temp);
        }
							
	}
#line 2031 "y.tab.c"
    break;

  case 32: /* statements: statement  */
#line 584 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statements");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statements:     statement"); 
    }
#line 2043 "y.tab.c"
    break;

  case 33: /* statements: statements statement  */
#line 592 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statements");
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statements:   statements statement"); 
    }
#line 2056 "y.tab.c"
    break;

  case 34: /* statement: var_declaration  */
#line 603 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statement");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:  var_declaration");
    }
#line 2068 "y.tab.c"
    break;

  case 35: /* statement: expression_statement  */
#line 611 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statement");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:    expression_statement"); 
    }
#line 2080 "y.tab.c"
    break;

  case 36: /* statement: compound_statement  */
#line 619 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statement");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:    compound_statement"); 
    }
#line 2092 "y.tab.c"
    break;

  case 37: /* statement: FOR LPAREN expression statement expression statement expression RPAREN statement  */
#line 627 "1905095.y"
    {

		(yyval.symbol)=new SymbolInfo((yyvsp[-8].symbol)->getName()+" "+(yyvsp[-7].symbol)->getName()+" "+(yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName(),"statement");
		(yyval.symbol)->addChild((yyvsp[-8].symbol));
        (yyval.symbol)->addChild((yyvsp[-7].symbol));
        (yyval.symbol)->addChild((yyvsp[-6].symbol));
        (yyval.symbol)->addChild((yyvsp[-5].symbol));
        (yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-8].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[-2].symbol)->getEndLine());
        showRule("statement:    FOR LPAREN expression_statement expression_statement expression RPAREN statement");
    }
#line 2111 "y.tab.c"
    break;

  case 38: /* statement: IF LPAREN expression RPAREN statement  */
#line 642 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statement");
		(yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-4].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:    IF LPAREN expression RPAREN statement");
    }
#line 2127 "y.tab.c"
    break;

  case 39: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 654 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+"\n"+(yyvsp[-1].symbol)->getName()+"\n"+(yyvsp[0].symbol)->getName(),"statement");
		(yyval.symbol)->addChild((yyvsp[-6].symbol));
        (yyval.symbol)->addChild((yyvsp[-5].symbol));
        (yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-6].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        showRule("statement:    IF LPAREN expression RPAREN statement ELSE statement");
    }
#line 2146 "y.tab.c"
    break;

  case 40: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 669 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statement");
		(yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-4].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:    WHILE LPAREN expression RPAREN statement");
    }
#line 2162 "y.tab.c"
    break;

  case 41: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 681 "1905095.y"
    {
		(yyval.symbol)=new SymbolInfo((yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName()+"\n","statement");
		(yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-4].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        showRule("statement:    PRINTLN LPAREN ID RPAREN SEMICOLON");
		SymbolInfo* lookedUp=symbolTable->lookUp((yyvsp[-2].symbol)->getName());
		if(lookedUp==NULL){
            error_out<<"Line# "<<lines<<": Undeclared variable "<<(yyvsp[-2].symbol)->getName()<<endl;
            errors++; 
		}
    }
#line 2184 "y.tab.c"
    break;

  case 42: /* statement: RETURN expression SEMICOLON  */
#line 699 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statement");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		showRule("statement:    RETURN expression SEMICOLON");
    }
#line 2198 "y.tab.c"
    break;

  case 43: /* expression_statement: SEMICOLON  */
#line 711 "1905095.y"
    {
		(yyval.symbol) = new SymbolInfo((yyvsp[0].symbol)->getName()+"\n","expression_statement");
		showRule("expression_statement:   SEMICOLON");
    }
#line 2207 "y.tab.c"
    break;

  case 44: /* expression_statement: expression SEMICOLON  */
#line 716 "1905095.y"
    {
		(yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName()+"\n","expression_statement");
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		showRule("expression_statement:   expression SEMICOLON");
    }
#line 2220 "y.tab.c"
    break;

  case 45: /* variable: ID  */
#line 727 "1905095.y"
    {
        showRule("variable: ID"); 
		SymbolInfo* lookedUp =symbolTable->lookUp((yyvsp[0].symbol)->getName());
        bool errorflag = false;
        string errorMessage;
        if(lookedUp==NULL){
            errorflag = true;
            errorMessage= "Undeclared variable "+(yyvsp[0].symbol)->getName();
            (yyval.symbol) = new SymbolInfo((yyvsp[0].symbol)->getName(),"variable");
            (yyval.symbol)->addChild((yyvsp[0].symbol));
            (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
            (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
            (yyval.symbol)->setStructure_type("var");
            (yyval.symbol)->setData_type("undefined"); 
        }
        else{
                if(lookedUp->getStructure_type()=="array"){
                    errorflag = true; 
                    errorMessage=lookedUp->getName()+ " is an array"; 
                }
                
                (yyval.symbol) = new SymbolInfo((yyvsp[0].symbol)->getName(),"variable");
                (yyval.symbol)->addChild((yyvsp[0].symbol));
                (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
                (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
                (yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
                (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        }

        if(errorflag==true){
            error_out<<"Line# "<<lines<<":  "<<errorMessage<<endl;
            errors++; 
        }
        else{
            (yyval.symbol)->setStructure_type(lookedUp->getStructure_type());
            (yyval.symbol)->setData_type(lookedUp->getData_type());
        }
    }
#line 2263 "y.tab.c"
    break;

  case 46: /* variable: ID LSQUARE expression RSQUARE  */
#line 766 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"variable");
		(yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-3].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("variable: ID LSQUARE expression RSQUARE");
        SymbolInfo* lookedUp =symbolTable->lookUp((yyvsp[-3].symbol)->getName());
        bool errorflag = false;
        string errorMessage;
        if(lookedUp==NULL){
            errorMessage= "Undeclared variable "+ (yyvsp[-3].symbol)->getName(); 
            errorflag= true; 
            (yyval.symbol)->setStructure_type("arrray");
            (yyval.symbol)->setData_type("undefined"); 
            
        }
        else {
            (yyval.symbol)->setStructure_type("array"); 
            (yyval.symbol)->setData_type(lookedUp->getData_type());
            if((yyvsp[-1].symbol)->getData_type().compare("int")!=0){
                string emessage= "Array subscript is not an integer"; 
                error_out<<"Line# "<<lines<<": "<<emessage<<endl;
                errors++; 
            }
        }


        if(errorflag==true){
            error_out<<"Line# "<<lines<<": "<<errorMessage<<endl;
            errors++; 
        }
    }
#line 2303 "y.tab.c"
    break;

  case 47: /* expression: logic_expression  */
#line 804 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"expression");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		(yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("expression:     logic_expression"); 
        debugString+=(yyvsp[0].symbol)->getName(); 
    }
#line 2318 "y.tab.c"
    break;

  case 48: /* expression: variable ASSIGNOP logic_expression  */
#line 815 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"expression");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("expression:   variable ASSIGNOP logic_expression"); 
		if((yyvsp[-2].symbol)->getData_type().compare("undefined")!=0 && (yyvsp[0].symbol)->getData_type().compare("undefined")!=0){
            if((yyvsp[-2].symbol)->getData_type().compare("void")==0 || (yyvsp[0].symbol)->getData_type().compare("void")==0 ){
                error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
                errors++;
            }
        }
		
        
		(yyval.symbol)->setData_type("int");
		(yyval.symbol)->setStructure_type((yyvsp[-2].symbol)->getStructure_type());
    }
#line 2342 "y.tab.c"
    break;

  case 49: /* logic_expression: rel_expression  */
#line 837 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"logic_expression");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("logic_expression: rel_expression"); 
    }
#line 2356 "y.tab.c"
    break;

  case 50: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 847 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"logic_expression");
		(yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type("int");
        (yyval.symbol)->setStructure_type((yyvsp[-2].symbol)->getStructure_type());
        showRule("logic_expression: rel_expression LOGICOP rel_expression");
        if((yyvsp[-2].symbol)->getData_type().compare("void")==0 || (yyvsp[0].symbol)->getData_type().compare("void")==0 ){
            error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
            errors++;
        }
    }
#line 2376 "y.tab.c"
    break;

  case 51: /* rel_expression: simple_expression  */
#line 865 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"rel_expression");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        (yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("rel_expression: simple_expression");
    }
#line 2390 "y.tab.c"
    break;

  case 52: /* rel_expression: simple_expression RELOP simple_expression  */
#line 875 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"rel_expression");
		(yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type("int");
        (yyval.symbol)->setStructure_type((yyvsp[-2].symbol)->getStructure_type());
        showRule("rel_expression:   simple_expression RELOP simple_expression");
        if((yyvsp[-2].symbol)->getData_type().compare("void")==0 || (yyvsp[0].symbol)->getData_type().compare("void")==0 ){
            error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
            errors++;
        }
    }
#line 2410 "y.tab.c"
    break;

  case 53: /* simple_expression: term  */
#line 893 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"simple_expression");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		(yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        showRule("simple_expression: term"); 
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
    }
#line 2424 "y.tab.c"
    break;

  case 54: /* simple_expression: simple_expression ADDOP term  */
#line 903 "1905095.y"
    {
		(yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"simple_expression");
		(yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        if((yyvsp[-2].symbol)->getData_type().compare("float")==0 || (yyvsp[0].symbol)->getData_type().compare("float")==0)
			(yyval.symbol)->setData_type("float");
		else if((yyvsp[-2].symbol)->getData_type().compare("int")==0 || (yyvsp[0].symbol)->getData_type().compare("int")==0)
			(yyval.symbol)->setData_type("int");
		else if((yyvsp[-2].symbol)->getData_type().compare("void")==0 || (yyvsp[0].symbol)->getData_type().compare("void")==0 ){
                error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
                errors++;
        }
        
        showRule("simple_expression: simple_expression ADDOP term"); 
    }
#line 2447 "y.tab.c"
    break;

  case 55: /* term: unary_expression  */
#line 926 "1905095.y"
    {
		(yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"term");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("term:   unary_expression"); 
        debugString+=(yyvsp[0].symbol)->getName(); 
    }
#line 2462 "y.tab.c"
    break;

  case 56: /* term: term MULOP unary_expression  */
#line 937 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"term");
		(yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        if((yyvsp[-2].symbol)->getData_type()=="void" || (yyvsp[0].symbol)->getData_type()=="void"){
                error_out<<"Line# "<<lines<<": function can't be void in expression"<<endl;
                errors++;        
        }

        if((yyvsp[-1].symbol)->getName()=="%"){
            if((yyvsp[-2].symbol)->getData_type()!="int" || (yyvsp[0].symbol)->getData_type()!="int"){
                error_out<<"Line# "<<lines<<": must mod an integer by another integer"<<endl;
                errors++;                
            }

            if((yyvsp[0].symbol)->getName()=="0"){
                error_out<<"Line# "<<lines<<": Warning, Divide by zero."<<endl;
                errors++;
            }
            (yyval.symbol)->setData_type("int");
        }
        else{
            if((yyvsp[-2].symbol)->getData_type()=="float" || (yyvsp[0].symbol)->getData_type()=="float"){
                (yyval.symbol)->setData_type("float");
            }
            else{
                (yyval.symbol)->setData_type("int");
            }
        }
    }
#line 2501 "y.tab.c"
    break;

  case 57: /* unary_expression: ADDOP unary_expression  */
#line 976 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"unary_expression");
		(yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		(yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        showRule("unary_expression:   ADDOP unary_expression");
    }
#line 2515 "y.tab.c"
    break;

  case 58: /* unary_expression: NOT unary_expression  */
#line 986 "1905095.y"
    {
		(yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"unary_expression");
		(yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        showRule("unary_expression: NOT unary_expression");
    }
#line 2529 "y.tab.c"
    break;

  case 59: /* unary_expression: factor  */
#line 996 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"unary_expression");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("unary_expression: factor"); 
    }
#line 2543 "y.tab.c"
    break;

  case 60: /* factor: variable  */
#line 1009 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"factor");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("factor:     variable");
		(yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
    }
#line 2557 "y.tab.c"
    break;

  case 61: /* $@7: %empty  */
#line 1019 "1905095.y"
                  {
        curr_call= (yyvsp[-1].symbol)->getName(); 

    }
#line 2566 "y.tab.c"
    break;

  case 62: /* factor: ID LPAREN $@7 argument_list RPAREN  */
#line 1023 "1905095.y"
    {
        if((yyvsp[-1].symbol)->getName() != "("){
            (yyval.symbol)=new SymbolInfo((yyvsp[-4].symbol)->getName()+(yyvsp[-3].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"factor");
            (yyval.symbol)->addChild((yyvsp[-4].symbol));
            (yyval.symbol)->addChild((yyvsp[-3].symbol));
            (yyval.symbol)->addChild((yyvsp[-1].symbol));
            (yyval.symbol)->addChild((yyvsp[0].symbol));
            (yyval.symbol)->setStartLine((yyvsp[-4].symbol)->getStartLine()); 
            (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		}
        else{
            (yyval.symbol)=new SymbolInfo((yyvsp[-4].symbol)->getName()+(yyvsp[-3].symbol)->getName()+(yyvsp[0].symbol)->getName(),"factor");
            (yyval.symbol)->addChild((yyvsp[-4].symbol));
            (yyval.symbol)->addChild((yyvsp[-3].symbol));
            (yyval.symbol)->addChild((yyvsp[0].symbol));
            (yyval.symbol)->setStartLine((yyvsp[-4].symbol)->getStartLine()); 
            (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        }


		
        SymbolInfo* lookedUp=symbolTable->lookUp((yyvsp[-4].symbol)->getName());
        showRule("factor:   ID LPAREN argument_list RPAREN"); 

		if(lookedUp==NULL){
            error_out<<"Line# "<<lines<<": Undeclared function '"<<(yyvsp[-4].symbol)->getName()<<"'"<<endl;
            errors++; 
			(yyval.symbol)->setData_type("undefined");
            parameter_list.clear();
		}
        else{
			vector<SymbolInfo> vec_temp = lookedUp->getParameterList();
            if(vec_temp.size()> parameter_list.size()){
                // error message                
            }
            else if(vec_temp.size()< parameter_list.size()){
                // error message                
            }
            int n= parameter_list.size(); 
            if(parameter_list.size()<vec_temp.size()){
                n = parameter_list.size();
            }
            for(int i=0; i<n; i++){
                
                if(vec_temp[i].getData_type() != parameter_list[i].getData_type()){
                    if(vec_temp[i].getData_type()=="float" && parameter_list[i].getData_type()=="int"){
                        ;
                    }
                    else{
                            error_out<<"Line# "<<lines<<": Type mismatch for argument "<<i<<" of "<<curr_call<<endl;
                            errors++;                         ;
                    }
                }
            }							
            parameter_list.clear();
            (yyval.symbol)->setData_type(lookedUp->getData_type());
	    }
    }
#line 2629 "y.tab.c"
    break;

  case 63: /* factor: LPAREN expression RPAREN  */
#line 1083 "1905095.y"
    {
        showRule("factor:   LPAREN expression RPAREN");
		(yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"factor");
		(yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

		(yyval.symbol)->setData_type((yyvsp[-1].symbol)->getData_type());
    }
#line 2645 "y.tab.c"
    break;

  case 64: /* factor: CONST_INT  */
#line 1095 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"factor");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        (yyval.symbol)->setData_type("int");
        showRule("factor:   CONST_INT"); 
		(yyval.symbol)->setStructure_type("val");
    }
#line 2660 "y.tab.c"
    break;

  case 65: /* factor: CONST_FLOAT  */
#line 1106 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"factor");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        (yyval.symbol)->setData_type("float");
        showRule("factor:   CONST_FLOAT"); 
		(yyval.symbol)->setStructure_type("val");
    }
#line 2675 "y.tab.c"
    break;

  case 66: /* factor: variable INCOP  */
#line 1117 "1905095.y"
    {
        showRule("factor:   variable INCOP"); 
		(yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"factor");
		(yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

    }
#line 2689 "y.tab.c"
    break;

  case 67: /* factor: variable DECOP  */
#line 1127 "1905095.y"
    {
        showRule("factor:   variable DECOP"); 
		(yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"factor");
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

    }
#line 2703 "y.tab.c"
    break;

  case 68: /* argument_list: arguments  */
#line 1139 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"argument_list");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        (yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());

        // parse_out<<debugGetType<<endl; 

        showRule("argument_list:  arguments"); 
	}
#line 2721 "y.tab.c"
    break;

  case 69: /* argument_list: %empty  */
#line 1152 "1905095.y"
          {
		(yyval.symbol)=new SymbolInfo(" ","argument_list");
        showRule("argument_list:  arguments"); 
    }
#line 2730 "y.tab.c"
    break;

  case 70: /* arguments: arguments COMMA logic_expression  */
#line 1159 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"arguments");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        debugString+=(yyvsp[-2].symbol)->getName(); 

        showRule("arguments:  arguments COMMA logic_expression"); 
		parameter_list.push_back(*(yyvsp[0].symbol));
    }
#line 2747 "y.tab.c"
    break;

  case 71: /* arguments: logic_expression  */
#line 1172 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"arguments");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

		(yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("arguments:    logic_expression");
        parameter_list.push_back(*(yyvsp[0].symbol));
    }
#line 2763 "y.tab.c"
    break;


#line 2767 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1185 "1905095.y"


int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Input File Name not Provided"); 
        return 0; 
    }

    FILE *fin = fopen(argv[1],"r"); 
    if(fin==NULL){
        printf("Can't open file\n"); 
        return 0; 
    }

    error_out.open("1905095_error.txt"); 
    log_out.open("1905095_log.txt"); 
    parse_out.open("1905095_parse_tree.txt");
    yyin = fin; 

    yyparse();

    fclose(yyin);
    error_out.close();
    log_out.close();
    parse_out.close();

    return 0; 
}
