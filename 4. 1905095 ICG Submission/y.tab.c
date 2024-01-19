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
#define ll long long int
#include <sstream>
#include <stdlib.h>
#include<string>
#include "1905095.cpp" 
#include<fstream>
#include<utility>
#include<string.h>
#include<map>
using namespace std; 

int yyparse(void);
void yyerror(char *s){
	printf("%s\n",s);
}

int yylex(void);

ofstream log_out; 
ofstream error_out;
ofstream parse_out;
ofstream temp_out; 
ofstream code_out; 
ofstream opt_out; 

extern FILE *yyin; 
SymbolTable* symbolTable = new SymbolTable(11);

extern ll lines; 
ll errors = 0;
ll labels = 0; 

string curr_type = "void";
string running_function = "global";
string curr_call = "global";
vector<SymbolInfo> parameter_list;
string label_begin; 
map<string, string> for_levels; 

void showRule(string ruleName){
    log_out<<ruleName<<endl;
}

string st= "";
vector<int> debug; 
string debugString =" "; 
string debugGetType=" "; 

bool is_main_func = false; 
string label_end_main; 

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

bool isGlobal(){
    if(symbolTable->getCurrent_scope()->getId()==1){
        return true; 
    }
    else{
        return false; 
    }
}

string newLabel(){
    return "L" + to_string(labels++);
}

string newLabel(string label){
    return label +"_"+ to_string(labels++);

}

void genCode(string st){
    temp_out<<st<<endl;
}

void comment_out(string st){
    temp_out<<"; line no: "<<lines<<" , "<<st<<endl<<endl; 
}

void gen_func_begin(string f_name)
{
    comment_out("Definition of Function "+f_name+" begins"); 
    temp_out << "\t" << f_name << " PROC"<<endl;
    if (f_name == "main")
    {
        label_end_main = newLabel();
        temp_out << "\t\tMOV AX, @DATA\n\t\tmov DS, AX"<<endl;
        is_main_func = true;
    }else{
        is_main_func = false;
        genCode("\t\tPUSH BP"); 
    }
    genCode("\t\tMOV BP, SP");
}

void gen_func_end(string f_name)
{
    if (f_name == "main")
    {
        temp_out << "\n\t\t" << label_end_main << ":" << endl;
        temp_out << "\t\tMOV AH, 4CH" << endl;
        temp_out << "\t\tINT 21H" << endl;
    }else{
        genCode("\t\tPOP BP");
        temp_out << "\t\tRET"<<endl;
        is_main_func = true;
    }
    temp_out << "\t" << f_name << " ENDP"<<endl<<endl;

    comment_out("Definition of Function "+f_name+" ends"); 

}



void genPrintfunction(){
    comment_out("Functions for printing new line and value of integer variables"); 
    temp_out<<"print_output PROC\n\tPUSH AX\n\tPUSH BX\n\tPUSH CX\n\tPUSH DX\n\tMOV CX, 10\n\tXOR BL, BL \n\tCMP AX, 0\n\tJGE STACK_OP \n\tMOV BH, 1\n\tNEG AX\nSTACK_OP:\n\tXOR DX, DX\n\tDIV CX\n\tPUSH DX\n\tINC BL \n\tCMP AX, 0\n\tJG STACK_OP\n\tMOV AH, 02\n\tCMP BH, 1 \n\tJNE PRINT_LOOP\n\tMOV DL, '-'\n\tINT 21H\nPRINT_LOOP:\n\tPOP DX\n\tXOR DH, DH\n\tADD DL, '0'\n\tINT 21H\n\tDEC BL\n\tCMP BL, 0\n\tJG PRINT_LOOP\n\tPOP DX\n\tPOP CX\n\tPOP BX\n\tPOP AX\n\tRET\n\tprint_output ENDP\n\n\tnew_line PROC\n\tPUSH AX\n\tPUSH DX\n\tMOV AH, 02\n\tMOV DL, 0DH\n\tINT 21H\n\tMOV DL, 0AH\n\tINT 21H\n\tPOP DX\n\tPOP AX\n\tRET\n\tnew_line ENDP\n\n\tEND main"<<endl;
}

void gen_peep_hole_optimization()
{
    ifstream code_in("1905095_code.asm");


    // optimize the code
    
    vector<string> codes;
    string line;
    while (getline(code_in, line))
    {
        codes.push_back(line);
    }
    int n= codes.size(); 

    for(int i=0;i<n; i++){
        if(codes[i].size()!=0){
            if(codes[i].substr(0,1)==";")
                continue;
        }
        if(codes[i].size()<2) {
            continue;
        }
        if(codes[i+1].size()<2){
            opt_out<<codes[i]<<endl;
            i++;
            continue; 
        }
        if(codes[i].size()<9){
            opt_out<<codes[i]<<endl;
            continue; 
        }
        if(codes[i+1].size()<8){
            opt_out<<codes[i+1]<<endl;
            i++;
            continue; 
        }

        if(codes[i].substr(2,4)=="PUSH" && codes[i+1].substr(2,3)=="POP"){
            if(codes[i].substr(7,2)==codes[i+1].substr(6,2)){
                opt_out<<";Removing redundant consecutive push and pop of the same register/address."<<endl;
                i++; 
                error_out<<endl;
                continue;    
             }          
        }
        if(codes[i].size()<10){
            opt_out<<codes[i]<<endl;
            continue; 
        }


        opt_out<<codes[i]<<endl;
    }
    opt_out.close();
    code_in.close();
}



void gen_asm_file(){
    ifstream temp_in("1905095_temp.asm");
    string line;
    while (getline(temp_in, line))
    {
        code_out << line << endl;
    }
    error_out<<"Here"<<endl; 
    gen_peep_hole_optimization(); 
    error_out<<"Done"<<endl; 

}




#line 303 "y.tab.c"

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
#line 233 "1905095.y"

    SymbolInfo* symbol; 

#line 446 "y.tab.c"

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
  YYSYMBOL_46_1 = 46,                      /* $@1  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_unit = 48,                      /* unit  */
  YYSYMBOL_func_declaration = 49,          /* func_declaration  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_51_3 = 51,                      /* $@3  */
  YYSYMBOL_func_definition = 52,           /* func_definition  */
  YYSYMBOL_53_4 = 53,                      /* $@4  */
  YYSYMBOL_54_5 = 54,                      /* $@5  */
  YYSYMBOL_parameter_list = 55,            /* parameter_list  */
  YYSYMBOL_compound_statement = 56,        /* compound_statement  */
  YYSYMBOL_57_6 = 57,                      /* $@6  */
  YYSYMBOL_58_7 = 58,                      /* $@7  */
  YYSYMBOL_var_declaration = 59,           /* var_declaration  */
  YYSYMBOL_type_specifier = 60,            /* type_specifier  */
  YYSYMBOL_declaration_list = 61,          /* declaration_list  */
  YYSYMBOL_statements = 62,                /* statements  */
  YYSYMBOL_statement = 63,                 /* statement  */
  YYSYMBOL_64_8 = 64,                      /* $@8  */
  YYSYMBOL_65_9 = 65,                      /* $@9  */
  YYSYMBOL_66_10 = 66,                     /* $@10  */
  YYSYMBOL_67_11 = 67,                     /* $@11  */
  YYSYMBOL_68_12 = 68,                     /* $@12  */
  YYSYMBOL_69_13 = 69,                     /* $@13  */
  YYSYMBOL_70_14 = 70,                     /* $@14  */
  YYSYMBOL_IF_Block = 71,                  /* IF_Block  */
  YYSYMBOL_72_15 = 72,                     /* $@15  */
  YYSYMBOL_expression_statement = 73,      /* expression_statement  */
  YYSYMBOL_variable = 74,                  /* variable  */
  YYSYMBOL_expression = 75,                /* expression  */
  YYSYMBOL_logic_expression = 76,          /* logic_expression  */
  YYSYMBOL_77_16 = 77,                     /* $@16  */
  YYSYMBOL_rel_expression = 78,            /* rel_expression  */
  YYSYMBOL_simple_expression = 79,         /* simple_expression  */
  YYSYMBOL_term = 80,                      /* term  */
  YYSYMBOL_unary_expression = 81,          /* unary_expression  */
  YYSYMBOL_factor = 82,                    /* factor  */
  YYSYMBOL_83_17 = 83,                     /* $@17  */
  YYSYMBOL_argument_list = 84,             /* argument_list  */
  YYSYMBOL_arguments = 85                  /* arguments  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   146

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

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
       0,   245,   245,   245,   267,   277,   288,   300,   308,   319,
     319,   354,   354,   382,   382,   447,   447,   489,   524,   545,
     567,   586,   586,   614,   614,   637,   658,   669,   680,   692,
     732,   790,   828,   887,   897,   910,   921,   934,   943,   947,
     959,   972,   943,  1007,  1021,  1021,  1044,  1050,  1044,  1079,
    1107,  1133,  1132,  1162,  1169,  1184,  1225,  1280,  1291,  1321,
    1331,  1331,  1396,  1406,  1449,  1459,  1504,  1514,  1587,  1603,
    1626,  1639,  1659,  1659,  1743,  1755,  1771,  1785,  1801,  1817,
    1831,  1837,  1851
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
  "start", "$@1", "program", "unit", "func_declaration", "$@2", "$@3",
  "func_definition", "$@4", "$@5", "parameter_list", "compound_statement",
  "$@6", "$@7", "var_declaration", "type_specifier", "declaration_list",
  "statements", "statement", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13",
  "$@14", "IF_Block", "$@15", "expression_statement", "variable",
  "expression", "logic_expression", "$@16", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor", "$@17",
  "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-91)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-24)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -91,     8,    24,   -91,   -91,   -91,   -91,    24,   -91,   -91,
     -91,   -91,    16,   -91,    44,    63,    38,    28,    23,   -91,
      19,    34,    46,    29,    37,    39,    58,    60,    24,   -91,
     -91,    91,   -91,    73,   -91,    68,    58,    96,    75,    72,
      82,   -91,   -91,   -91,   -91,   110,    57,   -91,   -91,    86,
      88,    89,   110,    90,   110,   110,   -91,   -91,   -91,   113,
       9,   -91,   111,   -91,    35,    92,   -91,    97,    87,   119,
     -91,   -91,   -91,    22,   -91,   -91,   110,   110,   -91,   -91,
      95,   117,   -91,   102,   100,   -91,   -91,   -91,   -91,   110,
     -91,   -91,   -91,   110,   110,   110,   110,   106,   104,   101,
     110,   -91,   105,   -91,    72,   -91,   110,   119,   130,   -91,
     -91,   112,   108,   -91,   -91,   -91,   114,   109,   -91,   -91,
     -91,   110,    72,   101,   -91,   -91,   -91,   -91,   -91,    72,
     110,   -91,   -91,   116,    72,   -91
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    27,    28,    26,     3,     5,     7,
       8,     6,     0,     4,    31,     0,     0,     0,     0,    25,
      11,     0,    20,     0,    29,     0,     0,     9,     0,    19,
      32,     0,    12,    21,    16,     0,     0,    18,     0,     0,
       0,    10,    14,    17,    30,     0,    55,    75,    76,     0,
       0,     0,     0,     0,     0,     0,    53,    37,    35,     0,
       0,    33,    43,    36,    71,     0,    57,    59,    62,    64,
      66,    70,    24,    71,    68,    72,     0,     0,    38,    46,
       0,     0,    69,     0,    31,    22,    34,    44,    77,     0,
      78,    54,    60,     0,     0,     0,    80,     0,     0,     0,
       0,    50,     0,    74,     0,    58,     0,    65,    63,    67,
      82,     0,    79,    56,    51,    39,     0,     0,    45,    61,
      73,     0,     0,     0,    47,    49,    81,    52,    40,     0,
       0,    48,    41,     0,     0,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,   -91,   -91,   131,   -91,   -91,   -91,   -91,   -91,
     -91,   -91,   -21,   -91,   -91,    61,     4,   -91,   -91,   -58,
     -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -90,
     -44,   -52,   -82,   -91,    40,    50,    52,   -41,   -91,   -91,
     -91,   -91
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,     8,     9,    35,    25,    10,    36,
      26,    21,    57,    39,    40,    58,    59,    15,    60,    61,
      99,   123,   130,   133,   104,   100,   129,    62,   122,    63,
      64,    65,    66,   106,    67,    68,    69,    70,    71,    96,
     111,   112
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,    73,    86,    83,    74,    34,    12,   105,     3,   115,
      73,    12,    45,    82,   110,    42,    46,    47,    48,    49,
      22,    50,    51,    14,    97,    98,     4,    88,     5,    52,
      24,    53,    37,   128,    54,    55,    23,    33,    85,   126,
      88,     4,    56,     5,     6,    73,   118,   -15,   116,    73,
      73,    73,    73,    29,   109,     4,    90,     5,    89,     6,
      30,    27,    73,    11,   127,    20,    28,    31,    11,    90,
      16,   131,    32,     6,    17,    45,   135,    73,   132,    46,
      47,    48,    49,    75,    50,    51,    33,    76,   -13,     4,
      93,     5,    52,    94,    53,    18,    19,    54,    55,    38,
      33,    41,   -23,    43,    45,    56,    44,     6,    46,    47,
      48,    72,    77,    45,    78,    79,    81,    46,    47,    48,
      84,    92,    87,    95,   102,    91,    54,    55,   101,   103,
      17,   114,   117,    93,    56,    54,    55,   113,    13,   120,
     121,   124,   125,   134,   108,   107,   119
};

static const yytype_uint8 yycheck[] =
{
      52,    45,    60,    55,    45,    26,     2,    89,     0,    99,
      54,     7,     3,    54,    96,    36,     7,     8,     9,    10,
      16,    12,    13,     7,    76,    77,    17,     5,    19,    20,
       7,    22,    28,   123,    25,    26,     8,    28,    29,   121,
       5,    17,    33,    19,    35,    89,   104,    28,   100,    93,
      94,    95,    96,     7,    95,    17,    34,    19,    23,    35,
      31,    27,   106,     2,   122,    27,    32,    30,     7,    34,
      26,   129,    33,    35,    30,     3,   134,   121,   130,     7,
       8,     9,    10,    26,    12,    13,    28,    30,    28,    17,
       3,    19,    20,     6,    22,    32,    33,    25,    26,     8,
      28,    33,    29,     7,     3,    33,    31,    35,     7,     8,
       9,    29,    26,     3,    26,    26,    26,     7,     8,     9,
       7,    24,    11,     4,     7,    33,    25,    26,    33,    27,
      30,    27,    27,     3,    33,    25,    26,    31,     7,    27,
      32,    27,    33,    27,    94,    93,   106
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,    46,     0,    17,    19,    35,    47,    48,    49,
      52,    59,    60,    48,     7,    61,    26,    30,    32,    33,
      27,    55,    60,     8,     7,    51,    54,    27,    32,     7,
      31,    30,    33,    28,    56,    50,    53,    60,     8,    57,
      58,    33,    56,     7,    31,     3,     7,     8,     9,    10,
      12,    13,    20,    22,    25,    26,    33,    56,    59,    60,
      62,    63,    71,    73,    74,    75,    76,    78,    79,    80,
      81,    82,    29,    74,    81,    26,    30,    26,    26,    26,
      75,    26,    81,    75,     7,    29,    63,    11,     5,    23,
      34,    33,    24,     3,     6,     4,    83,    75,    75,    64,
      69,    33,     7,    27,    68,    76,    77,    80,    79,    81,
      76,    84,    85,    31,    27,    73,    75,    27,    63,    78,
      27,    32,    72,    65,    27,    33,    76,    63,    73,    70,
      66,    63,    75,    67,    27,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    46,    45,    47,    47,    48,    48,    48,    50,
      49,    51,    49,    53,    52,    54,    52,    55,    55,    55,
      55,    57,    56,    58,    56,    59,    60,    60,    60,    61,
      61,    61,    61,    62,    62,    63,    63,    63,    64,    65,
      66,    67,    63,    63,    68,    63,    69,    70,    63,    63,
      63,    72,    71,    73,    73,    74,    74,    75,    75,    76,
      77,    76,    78,    78,    79,    79,    80,    80,    81,    81,
      81,    82,    83,    82,    82,    82,    82,    82,    82,    84,
      84,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     0,
       7,     0,     6,     0,     7,     0,     6,     4,     3,     2,
       1,     0,     4,     0,     3,     3,     1,     1,     1,     3,
       6,     1,     4,     1,     2,     1,     1,     1,     0,     0,
       0,     0,    11,     1,     0,     4,     0,     0,     7,     5,
       3,     0,     6,     1,     2,     1,     4,     1,     3,     1,
       0,     4,     1,     3,     1,     3,     1,     3,     2,     2,
       1,     1,     0,     5,     3,     1,     1,     2,     2,     1,
       0,     3,     1
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
  case 2: /* $@1: %empty  */
#line 245 "1905095.y"
       {

    code_out<<".MODEL SMALL\n.STACK 100h\n.DATA\n\tCR EQU 0DH\n\tLF EQU 0AH\n\tnumber DB \"00000\$\"\n\t"<<endl; 
    temp_out<<".CODE\n";

}
#line 1617 "y.tab.c"
    break;

  case 3: /* start: $@1 program  */
#line 251 "1905095.y"
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

        genPrintfunction();    
        gen_asm_file(); 
	}
#line 1636 "y.tab.c"
    break;

  case 4: /* program: program unit  */
#line 268 "1905095.y"
    {
        showRule("program : program unit");
        (yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"program");
        debugString+=(yyvsp[-1].symbol)->getName(); 
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine()); 
	}
#line 1650 "y.tab.c"
    break;

  case 5: /* program: unit  */
#line 278 "1905095.y"
    {
        showRule("program : unit");
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"program");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine()); 
	}
#line 1662 "y.tab.c"
    break;

  case 6: /* unit: var_declaration  */
#line 289 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"unit");
        showRule("unit : var_declaration");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        debugString+=(yyvsp[0].symbol)->getName(); 
        debugGetType+=(yyvsp[0].symbol)->getType(); 

	}
#line 1677 "y.tab.c"
    break;

  case 7: /* unit: func_declaration  */
#line 301 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"unit");
		showRule("unit : func_declaration");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
	}
#line 1689 "y.tab.c"
    break;

  case 8: /* unit: func_definition  */
#line 309 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"unit");
		showRule("unit : func_definition");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
    }
#line 1701 "y.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 319 "1905095.y"
                                                                   {
		running_function = (yyvsp[-3].symbol)->getName();
        debugString+=(yyvsp[-4].symbol)->getName(); 
		if(symbolTable->lookUp(running_function) == NULL){
			SymbolInfo* temp = new SymbolInfo(running_function, (yyvsp[-4].symbol)->getName());
			for(auto i : parameter_list){
				temp->addParameter(i);
                error_out<<"Parameter added "<<endl;
			}
			temp->setData_type((yyvsp[-4].symbol)->getName());
			temp->setStructure_type("func");
            temp->setType((yyvsp[-4].symbol)->getType()); 
			parameter_list.clear();
			symbolTable->InsertFunc(*temp);
		}
		else{
            error_out<<"Line# "<<lines<<": Redefinition of '"+running_function<<"'"<<endl; 
            errors++; 			
		}
        running_function = (yyvsp[-3].symbol)->getName();

	}
#line 1728 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN $@2 SEMICOLON  */
#line 340 "1905095.y"
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
#line 1746 "y.tab.c"
    break;

  case 11: /* $@3: %empty  */
#line 354 "1905095.y"
                                        {
			running_function=(yyvsp[-2].symbol)->getName();
			if(symbolTable->lookUp(running_function) == NULL){
				SymbolInfo* temp = new SymbolInfo(running_function, (yyvsp[-3].symbol)->getType());
                debugGetType+=(yyvsp[-3].symbol)->getType(); 
				temp->setStructure_type("func");
				temp->setData_type((yyvsp[-3].symbol)->getName());
				symbolTable->InsertFunc(*temp);
			}
			else{
                error_out<<"Line# "<<lines<<": Redeclaration of "+running_function<<endl; 
                errors++;				
			}
		}
#line 1765 "y.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN RPAREN $@3 SEMICOLON  */
#line 367 "1905095.y"
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
#line 1782 "y.tab.c"
    break;

  case 13: /* $@4: %empty  */
#line 382 "1905095.y"
                                                                {

    gen_func_begin((yyvsp[-3].symbol)->getName());

	running_function=(yyvsp[-3].symbol)->getName();
    debugString+=(yyvsp[-4].symbol)->getName(); 
    debugGetType+=(yyvsp[-4].symbol)->getType(); 
    
    SymbolInfo* temp = symbolTable->lookUp(running_function);

	if(temp == NULL){
		temp = new SymbolInfo(running_function,"FUNCTION" );

		for(auto i : parameter_list){
			temp->addParameter(i);
            error_out<<"Parameter added"<<endl; 
		}
		temp->setStructure_type("func");
		temp->setData_type((yyvsp[-4].symbol)->getName());
		symbolTable->InsertFunc(*temp);
       

	}
	else{
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
#line 1835 "y.tab.c"
    break;

  case 14: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@4 compound_statement  */
#line 429 "1905095.y"
                        {

    gen_func_end((yyvsp[-5].symbol)->getName());


    showRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
    string symName = (yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[0].symbol)->getName();
    debugString+=(yyvsp[-6].symbol)->getName(); 
    (yyval.symbol) = new SymbolInfo(symName, "func_definition");	
    (yyval.symbol)->addChild((yyvsp[-6].symbol));
    (yyval.symbol)->addChild((yyvsp[-5].symbol));
    (yyval.symbol)->addChild((yyvsp[-4].symbol));
    (yyval.symbol)->addChild((yyvsp[-3].symbol));
    (yyval.symbol)->addChild((yyvsp[-2].symbol));
    (yyval.symbol)->addChild((yyvsp[0].symbol));
    (yyval.symbol)->setStartLine((yyvsp[-6].symbol)->getStartLine()); 
    (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
    }
#line 1858 "y.tab.c"
    break;

  case 15: /* $@5: %empty  */
#line 447 "1905095.y"
                                      {

        gen_func_begin((yyvsp[-2].symbol)->getName());


        running_function=(yyvsp[-2].symbol)->getName();
        if(symbolTable->lookUp(running_function) == NULL){
            SymbolInfo* temp = new SymbolInfo(running_function, (yyvsp[-3].symbol)->getType());
            
            temp->setStructure_type("func");
            temp->setData_type((yyvsp[-3].symbol)->getName());
            symbolTable->InsertFunc(*temp);
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
#line 1887 "y.tab.c"
    break;

  case 16: /* func_definition: type_specifier ID LPAREN RPAREN $@5 compound_statement  */
#line 470 "1905095.y"
                                {

        gen_func_end((yyvsp[-4].symbol)->getName());

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
#line 1907 "y.tab.c"
    break;

  case 17: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 490 "1905095.y"
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

        (yyval.symbol)->setData_type((yyvsp[-3].symbol)->getData_type()); 

        (yyvsp[-1].symbol)->setData_type((yyvsp[-1].symbol)->getName()); 


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
#line 1946 "y.tab.c"
    break;

  case 18: /* parameter_list: parameter_list COMMA type_specifier  */
#line 525 "1905095.y"
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
        (yyvsp[0].symbol)->setData_type((yyvsp[0].symbol)->getName()); 
        (yyval.symbol)->setData_type((yyvsp[-2].symbol)->getData_type()); 


        
        parameter_list.push_back(*temp);
    }
#line 1971 "y.tab.c"
    break;

  case 19: /* parameter_list: type_specifier ID  */
#line 546 "1905095.y"
    {
        showRule("parameter_list  : type_specifier ID");
        string symName = (yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName();

        (yyval.symbol) = new SymbolInfo(symName, "type_specifier");
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        SymbolInfo* temp = new SymbolInfo((yyvsp[0].symbol)->getName(), (yyvsp[0].symbol)->getType());
        (yyvsp[-1].symbol)->setData_type((yyvsp[-1].symbol)->getName()); 
        temp->setStructure_type("var");
        temp->setData_type((yyvsp[-1].symbol)->getName());


        (yyvsp[-1].symbol)->setData_type((yyvsp[-1].symbol)->getName()); 
        (yyval.symbol)->setData_type((yyvsp[-1].symbol)->getName()); 


        parameter_list.push_back(*temp);
    }
#line 1997 "y.tab.c"
    break;

  case 20: /* parameter_list: type_specifier  */
#line 568 "1905095.y"
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

        (yyvsp[0].symbol)->setData_type((yyvsp[0].symbol)->getName()); 
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getName()); 

        parameter_list.push_back(*temp);
    }
#line 2018 "y.tab.c"
    break;

  case 21: /* $@6: %empty  */
#line 586 "1905095.y"
                              { 
        symbolTable->enter_scope(); 
        
        if(parameter_list.size() != 0){
            int j=0; 
            int n= parameter_list.size(); 
            for(auto i : parameter_list){
                int offset = 4 + (n - j) * 2;
                i.setIcg_name("W. [BP + "+to_string(offset)+ "]");
                symbolTable->Insert(i);
                j++; 
            }
        }
        parameter_list.clear();
    
    }
#line 2039 "y.tab.c"
    break;

  case 22: /* compound_statement: LCURL $@6 statements RCURL  */
#line 602 "1905095.y"
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
#line 2056 "y.tab.c"
    break;

  case 23: /* $@7: %empty  */
#line 614 "1905095.y"
              {
        symbolTable->enter_scope(); 
        
        if(parameter_list.size() != 0){
            for(auto i : parameter_list){
                symbolTable->Insert(i);
            }
        }
        parameter_list.clear();
    }
#line 2071 "y.tab.c"
    break;

  case 24: /* compound_statement: LCURL $@7 RCURL  */
#line 624 "1905095.y"
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
#line 2087 "y.tab.c"
    break;

  case 25: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 638 "1905095.y"
    {
    	(yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"var_declaration");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        
        (yyval.symbol)->setData_type((yyvsp[-2].symbol)->getName()); 

		showRule("var_declaration : type_specifier declaration_list SEMICOLON");
        if((yyvsp[-2].symbol)->getName() == "void"){
            error_out<<"Line# "<<lines<<": Variable or field '"<<(yyvsp[-2].symbol)->getName()<<"' declared void"<<endl; 
            errors++;
		}
	}
#line 2108 "y.tab.c"
    break;

  case 26: /* type_specifier: INT  */
#line 659 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo("int","type_specifier");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        debugString+=(yyvsp[0].symbol)->getName(); 
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type("int"); 
		showRule("type_specifier	: INT");
        curr_type="int"; 
	}
#line 2123 "y.tab.c"
    break;

  case 27: /* type_specifier: FLOAT  */
#line 670 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo("float","type_specifier");
        (yyval.symbol)->addChild((yyvsp[0].symbol)); 
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type("float"); 
    	showRule("type_specifier	: FLOAT");
        curr_type= "float"; 
				
	}
#line 2138 "y.tab.c"
    break;

  case 28: /* type_specifier: VOID  */
#line 681 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo("void","type_specifier");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type("void"); 
		showRule("type_specifier	: VOID");
        curr_type="void"; 
	}
#line 2152 "y.tab.c"
    break;

  case 29: /* declaration_list: declaration_list COMMA ID  */
#line 693 "1905095.y"
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

        if(isGlobal()==1){
            temp->setIcg_name((yyvsp[0].symbol)->getName()); 
            code_out<<"\t"<<temp->getName()<<" DW 1 DUP (0000H)"<<endl; 
            symbolTable->Insert(*temp);
        }
        else{
            symbolTable->addvar(); 
            temp_out<<"\t\tSUB SP,2\n"; 
            string str = "W.[BP-"+to_string(2*symbolTable->get_no_of_vars())+"]"; 
            temp->setIcg_name(str); 
            error_out<<temp->getIcg_name()<<" "<<temp->getName()<<" Declared"<<endl; 
            symbolTable->Insert(*temp);
        }
		
	}
#line 2195 "y.tab.c"
    break;

  case 30: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 733 "1905095.y"
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

        ll array_size = stoi((yyvsp[-1].symbol)->getName());
        temp->setArr_size(array_size);

        if(isGlobal()==true){
            temp->setIcg_name((yyvsp[-3].symbol)->getName()); 
            if(temp->getStructure_type()== "array"){
                code_out<<"\t"<<temp->getName()<<" DW "<<temp->getArr_size()<< " DUP (0000H)"<<endl; 

            }
            else{
                code_out<<"\t"<<temp->getName()<<" DW 1 DUP (0000H)"<<endl; 
            }
            symbolTable->Insert(*temp);

        }
        else{
             

            ll arr_begin = ((symbolTable->get_no_of_vars() + 1) * 2);
            string arr_addr = "W.[BP-" + to_string(arr_begin) + "]";
            temp->setIcg_name(arr_addr);
            temp->setArr_begin(arr_begin); 
            symbolTable->addvar(array_size);
            temp_out << "\t\tSUB SP, " << (array_size * 2) <<endl; 
            if(curr_type != "void"){
                symbolTable->Insert(*temp);
            }
            error_out<<temp->getIcg_name()<<endl;
            error_out << "line " << lines << ": ";
            error_out << "array " << temp->getName();
            error_out << " of size " << array_size << " declared\n";
        }        
						
	}
#line 2256 "y.tab.c"
    break;

  case 31: /* declaration_list: ID  */
#line 791 "1905095.y"
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
        // global scope 
        if(isGlobal()==true){
            temp->setIcg_name((yyvsp[0].symbol)->getName()); 
            code_out<<"\t"<<temp->getName()<<" DW 1 DUP (0000H)"<<endl; 
                symbolTable->Insert(*temp);
        }
        else{
            symbolTable->addvar(); 
            temp_out<<"\t\tSUB SP,2\n"; 
            string str = "W.[BP-"+to_string(2*symbolTable->get_no_of_vars())+"]"; 
            temp->setIcg_name(str); 
            error_out<<temp->getIcg_name()<<" "<<temp->getName()<<" Declared"<<endl; 
            symbolTable->Insert(*temp);

        }
        
        
				
	}
#line 2298 "y.tab.c"
    break;

  case 32: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 829 "1905095.y"
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

        ll array_size = stoi((yyvsp[-1].symbol)->getName());
        temp->setArr_size(array_size); 


        if(isGlobal()==true){
            if(temp->getStructure_type()== "array"){
                code_out<<"\t"<<temp->getName()<<" DW "<<temp->getArr_size()<< " DUP (0000H)"<<endl; 
                temp->setIcg_name((yyvsp[-3].symbol)->getName()); 
                symbolTable->Insert(*temp);
            }
            else{
                code_out<<"\t"<<temp->getName()<<" DW 1 DUP (0000H)"<<endl; 
                temp->setIcg_name((yyvsp[-3].symbol)->getName()); 
                symbolTable->Insert(*temp);            
            }
        }	
        else{
            
            ll arr_begin = ((symbolTable->get_no_of_vars() + 1) * 2);
            string arr_addr = "W.[BP-" + to_string(arr_begin) + "]";
            temp->setIcg_name(arr_addr);
            temp->setArr_begin(arr_begin); 
            symbolTable->addvar(array_size);
            temp_out << "\t\tSUB SP, " << (array_size * 2) <<endl; 
            if(curr_type != "void"){
                symbolTable->Insert(*temp);
            }

            error_out<<temp->getIcg_name()<<endl;
            error_out << "line " << lines << ": ";
            error_out << "array " << temp->getName();
            error_out << " of size " << array_size << " declared\n";
        }		            
							
	}
#line 2359 "y.tab.c"
    break;

  case 33: /* statements: statement  */
#line 888 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statements");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type()); 

        showRule("statements:     statement"); 
    }
#line 2373 "y.tab.c"
    break;

  case 34: /* statements: statements statement  */
#line 898 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statements");
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[-1].symbol)->getName()); 

        showRule("statements:   statements statement"); 
    }
#line 2388 "y.tab.c"
    break;

  case 35: /* statement: var_declaration  */
#line 911 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statement");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:  var_declaration");
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type()); 

        
    }
#line 2403 "y.tab.c"
    break;

  case 36: /* statement: expression_statement  */
#line 922 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statement");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:    expression_statement"); 
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type()); 
        genCode("\t\tPOP AX");
        comment_out("evaluated expression: "+(yyvsp[0].symbol)->getName());


    }
#line 2420 "y.tab.c"
    break;

  case 37: /* statement: compound_statement  */
#line 935 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statement");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type()); 
        showRule("statement:    compound_statement"); 
    }
#line 2433 "y.tab.c"
    break;

  case 38: /* $@8: %empty  */
#line 943 "1905095.y"
                    {
        comment_out("for loop starts here"); 
        comment_out("initializing iterator variable"); 
        for_levels.clear(); 
    }
#line 2443 "y.tab.c"
    break;

  case 39: /* $@9: %empty  */
#line 947 "1905095.y"
                            {
        for_levels["condition"] = newLabel("CONDITION");
		for_levels["statement"] = newLabel("STATEMENT");
		for_levels["inc_dec"] = newLabel("INC_DEC");
		for_levels["end_for"] = newLabel("END_FOR");

		genCode("\t\tPOP AX");
        comment_out(" initialization of iterator done for for_loop, expression: "+(yyvsp[0].symbol)->getName()+"\n");
        
        comment_out("Now condition check for for_loop begins"); 
		genCode("\t\t"+for_levels["condition"]+":"); 

    }
#line 2461 "y.tab.c"
    break;

  case 40: /* $@10: %empty  */
#line 959 "1905095.y"
                            {
        genCode("\t\tPOP AX"); 
		genCode("\t\tCMP AX, 0");
        comment_out("Break for loop");
		genCode("\t\tJE "+for_levels["end_for"]); 

        comment_out("execute statement ");

		genCode("\t\tJMP "+for_levels["statement"]);

        comment_out("increment or decrement of iterator variable");
		genCode("\t\t"+for_levels["inc_dec"]+":");

    }
#line 2480 "y.tab.c"
    break;

  case 41: /* $@11: %empty  */
#line 972 "1905095.y"
                    {
        genCode("\t\tPOP AX");
        comment_out("Increment or Decrement done for expression: "+(yyvsp[0].symbol)->getName()+"\n");

        comment_out("continue loop, again goes for condition check"); 
		genCode("\t\tJMP "+for_levels["condition"]);

        comment_out("statement of for loop starts");
		genCode("\t\t"+for_levels["statement"]+":");

    }
#line 2496 "y.tab.c"
    break;

  case 42: /* statement: FOR LPAREN $@8 expression_statement $@9 expression_statement $@10 expression $@11 RPAREN statement  */
#line 983 "1905095.y"
    {

		(yyval.symbol)=new SymbolInfo((yyvsp[-10].symbol)->getName()+" "+(yyvsp[-9].symbol)->getName()+" "+(yyvsp[-7].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statement");
		(yyval.symbol)->addChild((yyvsp[-10].symbol));
        (yyval.symbol)->addChild((yyvsp[-9].symbol));
        (yyval.symbol)->addChild((yyvsp[-7].symbol));
        (yyval.symbol)->addChild((yyvsp[-5].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-10].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:    FOR LPAREN expression_statement expression_statement expression RPAREN statement");

        comment_out("Jump to increment or decrement state"); 
        genCode("\t\tJMP "+for_levels["inc_dec"]);

        comment_out("For Loop ends here"); 

        comment_out("Ending block for for_loop"); 
		genCode("\t\t"+for_levels["end_for"]+":"); 
    }
#line 2523 "y.tab.c"
    break;

  case 43: /* statement: IF_Block  */
#line 1008 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"statement");
		(yyval.symbol)->addChild((yyvsp[0].symbol));

        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("statement:    IF LPAREN expression RPAREN statement");



        genCode("\t\t"+(yyvsp[0].symbol)->get_label()+":\n");
    }
#line 2540 "y.tab.c"
    break;

  case 44: /* $@12: %empty  */
#line 1021 "1905095.y"
                        {
        comment_out("Else block begins ");
        string label = newLabel("END_ELSE");
		genCode("\t\tJMP "+label); 
		genCode("\t\t"+(yyvsp[-1].symbol)->get_label()+":\n");
		(yyvsp[-1].symbol)->set_label(label);
    }
#line 2552 "y.tab.c"
    break;

  case 45: /* statement: IF_Block ELSE $@12 statement  */
#line 1028 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statement");
		(yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        
        (yyval.symbol)->setStartLine((yyvsp[-3].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
               
        comment_out("Else block ends");
        genCode("\t\t"+(yyvsp[-3].symbol)->get_label()+":\n");


        showRule("statement:    IF LPAREN expression RPAREN statement ELSE statement");
    }
#line 2572 "y.tab.c"
    break;

  case 46: /* $@13: %empty  */
#line 1044 "1905095.y"
                        {
        
        comment_out("while loop starts here"); 

        label_begin = newLabel("WHILE");
		genCode("\t"+label_begin+":");
    }
#line 2584 "y.tab.c"
    break;

  case 47: /* $@14: %empty  */
#line 1050 "1905095.y"
                           {

        comment_out("While block begins..."); 
		string label_end = newLabel("END_WHILE");
		genCode("\t\tPOP AX");
        comment_out((yyvsp[-1].symbol)->getName()+ " loaded"); 
		genCode("\t\tCMP AX,0");
		genCode("\t\tJE "+label_end);
		(yyvsp[-1].symbol)->set_label(label_begin+" "+label_end);
    }
#line 2599 "y.tab.c"
    break;

  case 48: /* statement: WHILE LPAREN $@13 expression RPAREN $@14 statement  */
#line 1060 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statement");
		(yyval.symbol)->addChild((yyvsp[-6].symbol));
        (yyval.symbol)->addChild((yyvsp[-5].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-6].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        stringstream ss((yyvsp[-3].symbol)->get_label());
		string a, b;
		ss >> a >> b;
		genCode("\t\tJMP "+a);
		genCode("\t"+b+":\n");

        showRule("statement:    WHILE LPAREN expression RPAREN statement");
    }
#line 2622 "y.tab.c"
    break;

  case 49: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 1080 "1905095.y"
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
        else{
            error_out<<lookedUp->getIcg_name()<<endl;
            comment_out("println("+(yyvsp[-2].symbol)->getName()+")"); 

            string tempSt= "\t\tMOV AX, "+lookedUp->getIcg_name(); 
			genCode(tempSt);
            comment_out((yyvsp[-2].symbol)->getName()+" loaded"); 
			genCode("\t\tCALL print_output");
            genCode("\t\tCALL new_line");
        }
    }
#line 2654 "y.tab.c"
    break;

  case 50: /* statement: RETURN expression SEMICOLON  */
#line 1108 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"statement");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		showRule("statement:    RETURN expression SEMICOLON");
        if(is_main_func==false){

			genCode("\t\tPOP AX");
            comment_out((yyvsp[-1].symbol)->getName()+ " loaded"); 
			genCode("\t\tMOV [BP+4], AX"); 

            comment_out("Removing all internal variables from stack"); 
			genCode("\t\tADD SP, "+to_string(symbolTable->get_no_of_vars()*2));

			genCode("\t\tPOP BP"); 	
			genCode("\t\tRET"); 
        }
    }
#line 2680 "y.tab.c"
    break;

  case 51: /* $@15: %empty  */
#line 1133 "1905095.y"
    {        
        string label = newLabel("END_IF");

        (yyvsp[-1].symbol)->set_label(label); 
        
        genCode("\t\tPOP AX");
        comment_out((yyvsp[-1].symbol)->getName()+ " loaded"); 
        genCode("\t\tCMP AX, 0");

        comment_out("If block begins"); 
        genCode("\t\tJE "+label);

    }
#line 2698 "y.tab.c"
    break;

  case 52: /* IF_Block: IF LPAREN expression RPAREN $@15 statement  */
#line 1145 "1905095.y"
                {
        
        comment_out("If block ends"); 
        (yyval.symbol)= new SymbolInfo((yyvsp[-5].symbol)->getName()+" "+ (yyvsp[-4].symbol)->getName()+ " "+ (yyvsp[-3].symbol)->getName()+ " "+ (yyvsp[-2].symbol)->getName()+ " "+ (yyvsp[0].symbol)->getName(), "IF_Block"); 
        (yyval.symbol)->set_label((yyvsp[-3].symbol)->get_label()); 

        (yyval.symbol)->addChild((yyvsp[-5].symbol));
        (yyval.symbol)->addChild((yyvsp[-4].symbol));
        (yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol)); 
        (yyval.symbol)->addChild((yyvsp[0].symbol)); 
        (yyval.symbol)->setStartLine((yyvsp[-5].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
    }
#line 2717 "y.tab.c"
    break;

  case 53: /* expression_statement: SEMICOLON  */
#line 1163 "1905095.y"
    {
		(yyval.symbol) = new SymbolInfo((yyvsp[0].symbol)->getName()+"\n","expression_statement");
		showRule("expression_statement:   SEMICOLON");
        comment_out("1 for infinite loop");
		genCode("\t\tPUSH 1");
    }
#line 2728 "y.tab.c"
    break;

  case 54: /* expression_statement: expression SEMICOLON  */
#line 1170 "1905095.y"
    {


		(yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName()+"\n","expression_statement");
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[-1].symbol)->getData_type()); 

		showRule("expression_statement:   expression SEMICOLON");
    }
#line 2745 "y.tab.c"
    break;

  case 55: /* variable: ID  */
#line 1185 "1905095.y"
    {
        showRule("variable: ID"); 
		SymbolInfo* lookedUp =symbolTable->lookUp((yyvsp[0].symbol)->getName());
        bool errorflag = false;
        string errorMessage;
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type()); 
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
                (yyval.symbol)->setIcg_name(lookedUp->getIcg_name()); 
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
#line 2790 "y.tab.c"
    break;

  case 56: /* variable: ID LSQUARE expression RSQUARE  */
#line 1226 "1905095.y"
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

            (yyvsp[-3].symbol)->copy_symbol(*lookedUp);
            
            comment_out((yyval.symbol)->getName()); 
            comment_out("Popping index "+(yyvsp[0].symbol)->getName()+" of the array "+(yyvsp[-3].symbol)->getName()); 
			genCode("\t\tPOP AX");
            comment_out("Multiplying by 2 , returns offset"); 
			genCode("\t\tSHL AX, 1");
            comment_out("Array base address"); 
			genCode("\t\tLEA BX, "+lookedUp->getIcg_name());
			genCode("\t\tSUB BX, AX");
			genCode("\t\tPUSH BX");
			(yyvsp[-3].symbol)->setIcg_name("[BX]");
            (yyval.symbol)->setIcg_name((yyvsp[-3].symbol)->getIcg_name()); 
        }


        if(errorflag==true){
            error_out<<"Line# "<<lines<<": "<<errorMessage<<endl;
            errors++; 
        }
    }
#line 2847 "y.tab.c"
    break;

  case 57: /* expression: logic_expression  */
#line 1281 "1905095.y"
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
#line 2862 "y.tab.c"
    break;

  case 58: /* expression: variable ASSIGNOP logic_expression  */
#line 1292 "1905095.y"
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
		
        comment_out((yyval.symbol)->getName()); 
		(yyval.symbol)->setData_type("int");
		(yyval.symbol)->setStructure_type((yyvsp[-2].symbol)->getStructure_type());
        genCode("\t\tPOP AX");
        comment_out((yyvsp[0].symbol)->getName()+ " loaded"); 
        if ((yyvsp[-2].symbol)->getStructure_type()=="array" && isGlobal()==false)
            genCode("\t\tPOP BX");
		genCode("\t\tMOV "+(yyvsp[-2].symbol)->getIcg_name()+", AX");
		genCode("\t\tPUSH AX");


    }
#line 2894 "y.tab.c"
    break;

  case 59: /* logic_expression: rel_expression  */
#line 1322 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"logic_expression");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("logic_expression: rel_expression"); 
    }
#line 2908 "y.tab.c"
    break;

  case 60: /* $@16: %empty  */
#line 1331 "1905095.y"
                                {

        comment_out("For expression: "+ (yyvsp[-1].symbol)->getName()+ " , Short circuit code for jumping");
		genCode("\t\tPOP AX");
        comment_out((yyvsp[-1].symbol)->getName()+ " loaded");
		string check; 
        if((yyvsp[0].symbol)->getName()=="&&"){
            check= "1"; 
        }
        else{
            check ="0"; 
        }
		genCode("\t\tCMP AX, "+check);
		string j_label = newLabel();
		genCode("\t\tJNE "+j_label);
		(yyvsp[-1].symbol)->set_label(j_label);

    }
#line 2931 "y.tab.c"
    break;

  case 61: /* logic_expression: rel_expression LOGICOP $@16 rel_expression  */
#line 1349 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-3].symbol)->getName()+" "+(yyvsp[-2].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"logic_expression");
		(yyval.symbol)->addChild((yyvsp[-3].symbol));
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-3].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type("int");
        (yyval.symbol)->setStructure_type((yyvsp[-3].symbol)->getStructure_type());
        showRule("logic_expression: rel_expression LOGICOP rel_expression");
        if((yyvsp[-3].symbol)->getData_type().compare("void")==0 || (yyvsp[0].symbol)->getData_type().compare("void")==0 ){
            error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
            errors++;
        }

        comment_out((yyval.symbol)->getName());
		genCode("\t\tPOP AX");
        comment_out((yyvsp[0].symbol)->getName()+" loaded"); 
		string boolVal = (yyvsp[-2].symbol)->getName() == "&&" ? "1" : "0";


		genCode("\t\tCMP AX, "+boolVal);
		genCode("\t\tJNE "+(yyvsp[-3].symbol)->get_label());

        string check; 
        if((yyvsp[-2].symbol)->getName()=="&&"){
            check= "1"; 
        }
        else{
            check ="0"; 
        }
		genCode("\t\t\tPUSH "+check);
		string logic_label = newLabel();
		genCode("\t\t\tJMP "+logic_label);
		genCode("\t\t"+(yyvsp[-3].symbol)->get_label()+":");
        if((yyvsp[-2].symbol)->getName()=="&&"){
            check= "0"; 
        }
        else{
            check ="1"; 
        }
		genCode("\t\t\tPUSH " +check);
		genCode("\t\t"+logic_label+":\n");

    }
#line 2981 "y.tab.c"
    break;

  case 62: /* rel_expression: simple_expression  */
#line 1397 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"rel_expression");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        (yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("rel_expression: simple_expression");
    }
#line 2995 "y.tab.c"
    break;

  case 63: /* rel_expression: simple_expression RELOP simple_expression  */
#line 1407 "1905095.y"
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

        string true_label = newLabel();
		string end_label = newLabel();

        string relat_op; 
        
        if((yyvsp[-1].symbol)->getName() == "<") relat_op= "JL";
        if((yyvsp[-1].symbol)->getName() == "<=") relat_op= "JLE";
        if((yyvsp[-1].symbol)->getName() == ">") relat_op= "JG";
        if((yyvsp[-1].symbol)->getName() == ">=") relat_op= "JGE";
        if((yyvsp[-1].symbol)->getName() == "==") relat_op= "JE";
        if((yyvsp[-1].symbol)->getName() == "!=") relat_op= "JNE";

        comment_out((yyval.symbol)->getName());
        genCode("\t\tPOP BX");
        comment_out((yyvsp[0].symbol)->getName()+ " loaded"); 
		genCode("\t\tPOP AX");
        comment_out((yyvsp[-2].symbol)->getName()+ " loaded"); 
		genCode("\t\tCMP AX, BX");
		genCode("\t\t"+relat_op+" "+true_label);
		genCode("\t\t\tPUSH 0"); 
        genCode("\t\t\tJMP "+end_label); 
		genCode("\t\t"+true_label+":\n\t\t\tPUSH 1");
		genCode("\t\t"+end_label+":\n");

    }
#line 3040 "y.tab.c"
    break;

  case 64: /* simple_expression: term  */
#line 1450 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"simple_expression");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		(yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        showRule("simple_expression: term"); 
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
    }
#line 3054 "y.tab.c"
    break;

  case 65: /* simple_expression: simple_expression ADDOP term  */
#line 1460 "1905095.y"
    {

		(yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+" "+(yyvsp[-1].symbol)->getName()+ " "+ (yyvsp[0].symbol)->getName(),"simple_expression");
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
        else{
            error_out<<"Invalid data type"<<endl; 

        }
        comment_out((yyval.symbol)->getName()); 

        genCode("\t\tPOP BX");
        comment_out((yyvsp[0].symbol)->getName()+ " loaded"); 

		genCode("\t\tPOP AX");
        comment_out((yyvsp[-2].symbol)->getName()+ " loaded"); 
        string addst; 
        if((yyvsp[-1].symbol)->getName()=="+"){
            addst = "ADD";
        }
        else{
            addst= "SUB"; 
        }
		genCode("\t\t"+addst+" AX, BX");
		genCode("\t\tPUSH AX");
        comment_out((yyvsp[-2].symbol)->getName()+ " stored"); 
        
        showRule("simple_expression: simple_expression ADDOP term"); 
    }
#line 3099 "y.tab.c"
    break;

  case 66: /* term: unary_expression  */
#line 1505 "1905095.y"
    {
		(yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"term");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("term:   unary_expression"); 
    }
#line 3113 "y.tab.c"
    break;

  case 67: /* term: term MULOP unary_expression  */
#line 1515 "1905095.y"
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

        if((yyvsp[-1].symbol)->getName()=="%"|| (yyvsp[-1].symbol)->getName()=="/"){
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

        comment_out((yyval.symbol)->getName()); 
        genCode("\t\tPOP BX");
        comment_out((yyvsp[0].symbol)->getName()+ " loaded"); 

		genCode("\t\tPOP AX");
        comment_out((yyvsp[-2].symbol)->getName()+ " loaded"); 

		genCode("\t\tXOR DX, DX");
        comment_out("DX Register cleared"); 

		string mulst;
        if((yyvsp[-1].symbol)->getName()=="*"){
            mulst = "IMUL"; 
        }
        else{
            mulst= "IDIV"; 
        }
		genCode("\t\t"+mulst+" BX");

        string mulres; 

        if((yyvsp[-1].symbol)->getName()=="%"){
            mulres = "DX";
        }
        else{
            mulres="AX"; 
        }

		genCode("\t\tPUSH "+mulres);

        showRule("term:   MULOP unary_expression"); 

    }
#line 3186 "y.tab.c"
    break;

  case 68: /* unary_expression: ADDOP unary_expression  */
#line 1588 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"unary_expression");
		(yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
		(yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        showRule("unary_expression:   ADDOP unary_expression");
        if((yyvsp[-1].symbol)->getName() == "-"){
            comment_out((yyval.symbol)->getName()); 
			genCode("\t\tPOP AX");
			genCode("\t\tNEG AX");
			genCode("\t\tPUSH AX\n");
		}
    }
#line 3206 "y.tab.c"
    break;

  case 69: /* unary_expression: NOT unary_expression  */
#line 1604 "1905095.y"
    {
		(yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"unary_expression");
		(yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
        showRule("unary_expression: NOT unary_expression");

        string not_label1 = newLabel();
		string not_label2 = newLabel(); 
		comment_out((yyval.symbol)->getName());
		genCode("\t\tPOP AX");
		genCode("\t\tCMP AX, 0");
		genCode("\t\tJE "+not_label1);
		genCode("\t\t\tPUSH 0");
		genCode("\t\t\tJMP "+not_label2);
		genCode("\t\t"+not_label1+":"); 
        genCode("\n\t\tPUSH 1\n");
		genCode("\t\t"+not_label2+":");

    }
#line 3233 "y.tab.c"
    break;

  case 70: /* unary_expression: factor  */
#line 1627 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"unary_expression");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        (yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());
        showRule("unary_expression: factor"); 
    }
#line 3247 "y.tab.c"
    break;

  case 71: /* factor: variable  */
#line 1640 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"factor");
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        showRule("factor:     variable");
		(yyval.symbol)->setData_type((yyvsp[0].symbol)->getData_type());
		(yyval.symbol)->setStructure_type((yyvsp[0].symbol)->getStructure_type());

        if ((yyvsp[0].symbol)->getStructure_type()=="array" && isGlobal()==false)
            genCode("\t\tPOP BX");

        genCode("\t\tPUSH "+(yyvsp[0].symbol)->getIcg_name());

        comment_out((yyvsp[0].symbol)->getName()+ " stored"); 


    }
#line 3270 "y.tab.c"
    break;

  case 72: /* $@17: %empty  */
#line 1659 "1905095.y"
                  {
        curr_call= (yyvsp[-1].symbol)->getName(); 

    }
#line 3279 "y.tab.c"
    break;

  case 73: /* factor: ID LPAREN $@17 argument_list RPAREN  */
#line 1663 "1905095.y"
    {
        SymbolInfo* lookedUp=symbolTable->lookUp((yyvsp[-4].symbol)->getName());
        showRule("factor:   ID LPAREN argument_list RPAREN"); 

        (yyval.symbol)->setData_type(lookedUp->getData_type());
        int size; 

		if(lookedUp==NULL){


            error_out<<"Line# "<<lines<<": Undeclared function '"<<(yyvsp[-4].symbol)->getName()<<"'"<<endl;
            errors++; 
			(yyval.symbol)->setData_type("undefined");
            parameter_list.clear();
		}
        else{


			vector<SymbolInfo> vec_temp = lookedUp->getParameterList();
            size= vec_temp.size(); 

            if(vec_temp.size()> parameter_list.size()){
                error_out<<"Total Number of arguments less in the function "<<lines<<endl; 
            }
            else if(vec_temp.size()< parameter_list.size()){
                error_out<<"Total Number of arguments greater in the function "<<lines<<endl; 

            }

            int n= vec_temp.size(); 
            if(parameter_list.size()<vec_temp.size()){
                n = parameter_list.size();
            }

               
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

        
            (yyval.symbol)->setData_type(lookedUp->getData_type());

            parameter_list.clear();

	    }

        comment_out("For return value"); 
        genCode("\t\tPUSH 0"); 
        
        comment_out("Calling function "+ (yyvsp[-4].symbol)->getName()); 
		genCode("\t\tCALL "+(yyvsp[-4].symbol)->getName());
		genCode("\t\tPOP AX");
        comment_out("Return value loaded"); 

        comment_out("Now removing function parameters from the stack"); 
		genCode("\t\tADD SP,"+to_string(size*2));
		if((yyvsp[-4].symbol)->getData_type() != "void"){
            comment_out("Return value stored "); 
			genCode("\t\tPUSH AX");
		}else{
            comment_out("For void function , default return value set to 0 "); 
			genCode("\t\tPUSH 0");
		}

    }
#line 3363 "y.tab.c"
    break;

  case 74: /* factor: LPAREN expression RPAREN  */
#line 1744 "1905095.y"
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
#line 3379 "y.tab.c"
    break;

  case 75: /* factor: CONST_INT  */
#line 1756 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"factor");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        (yyval.symbol)->setData_type("int");
        showRule("factor:   CONST_INT"); 
		(yyval.symbol)->setStructure_type("val");

        comment_out("Store "+ (yyvsp[0].symbol)->getName()); 
        genCode("\t\tPUSH " + (yyvsp[0].symbol)->getName());


    }
#line 3399 "y.tab.c"
    break;

  case 76: /* factor: CONST_FLOAT  */
#line 1772 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[0].symbol)->getName(),"factor");
		(yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[0].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        (yyval.symbol)->setData_type("float");
        showRule("factor:   CONST_FLOAT"); 
		(yyval.symbol)->setStructure_type("val");
        comment_out("Store "+ (yyvsp[0].symbol)->getName()); 
        genCode("\t\tPUSH " + (yyvsp[0].symbol)->getName());

    }
#line 3417 "y.tab.c"
    break;

  case 77: /* factor: variable INCOP  */
#line 1786 "1905095.y"
    {
        showRule("factor:   variable INCOP"); 
		(yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"factor");
		(yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        if ((yyvsp[-1].symbol)->getStructure_type()=="array" && isGlobal()==false)
            genCode("\t\tPOP BX");
        comment_out("Store "+ (yyvsp[-1].symbol)->getName()); 
        genCode("\t\tPUSH " + (yyvsp[-1].symbol)->getIcg_name());
        comment_out("Incremnt of "+ (yyvsp[-1].symbol)->getName()); 
        genCode("\t\tINC " + (yyvsp[-1].symbol)->getIcg_name());

    }
#line 3437 "y.tab.c"
    break;

  case 78: /* factor: variable DECOP  */
#line 1802 "1905095.y"
    {
        showRule("factor:   variable DECOP"); 
		(yyval.symbol)=new SymbolInfo((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName(),"factor");
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-1].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());
        comment_out("Store "+ (yyvsp[-1].symbol)->getName()); 
        genCode("\t\tPUSH " + (yyvsp[-1].symbol)->getIcg_name());
        comment_out("Decrement of "+ (yyvsp[-1].symbol)->getName()); 
        genCode("\t\tDEC "+ (yyvsp[-1].symbol)->getIcg_name());

    }
#line 3455 "y.tab.c"
    break;

  case 79: /* argument_list: arguments  */
#line 1818 "1905095.y"
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
#line 3473 "y.tab.c"
    break;

  case 80: /* argument_list: %empty  */
#line 1831 "1905095.y"
          {
		(yyval.symbol)=new SymbolInfo(" ","argument_list");
        showRule("argument_list:  arguments"); 
    }
#line 3482 "y.tab.c"
    break;

  case 81: /* arguments: arguments COMMA logic_expression  */
#line 1838 "1905095.y"
    {
        (yyval.symbol)=new SymbolInfo((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName(),"arguments");
        (yyval.symbol)->addChild((yyvsp[-2].symbol));
        (yyval.symbol)->addChild((yyvsp[-1].symbol));
        (yyval.symbol)->addChild((yyvsp[0].symbol));
        (yyval.symbol)->setStartLine((yyvsp[-2].symbol)->getStartLine()); 
        (yyval.symbol)->setEndLine((yyvsp[0].symbol)->getEndLine());

        showRule("arguments:  arguments COMMA logic_expression");

 
		parameter_list.push_back(*(yyvsp[0].symbol));
    }
#line 3500 "y.tab.c"
    break;

  case 82: /* arguments: logic_expression  */
#line 1852 "1905095.y"
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
#line 3516 "y.tab.c"
    break;


#line 3520 "y.tab.c"

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

#line 1865 "1905095.y"


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
    temp_out.open("1905095_temp.asm"); 
    code_out.open("1905095_code.asm"); 
    opt_out.open("1905095_optimized_code.asm");


    yyin = fin; 

    yyparse();

    fclose(yyin);
    error_out.close();
    log_out.close();
    parse_out.close();

    return 0; 
}
