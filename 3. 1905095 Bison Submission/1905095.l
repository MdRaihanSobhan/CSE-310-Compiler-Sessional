%option noyywrap 

%x str_State
%x multi_str_State
%x ch_State
%x single_Comment
%x multiple_Comment


%{
#include<iostream>
#include<stdio.h>
#include<cstring>
#include "1905095.cpp" 
#define ll long long int
#include <sstream>
#include "y.tab.h"
using namespace std;



void yyerror(char*);
extern YYSTYPE yylval; 

string st1; // exact char print          
string st2; // /t /a / 
string ch1;
string ch2;
string res; // "string"
string cmnt; 

ll lines = 1; 
extern ll errors; 
ll innerNL = 0; 

char ch; 

extern ofstream error_out; 
extern ofstream log_out; 


void showToken(ll lineNo, string tokenName, string tokenType){
    log_out<<"Line# "<<lineNo<<": Token <"<<tokenType<<"> Lexeme "<<tokenName<<" found"<<endl;
}



%}

WHITESPACE [ \t\f\r\v]+
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE [\r]?\n
AlphaNumeric [A-Za-z_0-9] 
ID [_A-Za-z][A-Za-z_0-9]* 
Integer {DIGIT}+
Floating_Point {DIGIT}*(\.{DIGIT}+)?([Ee][+-]?{DIGIT}+)?
Too_Many_Decimal_Points {DIGIT}+\.{DIGIT}+\.({DIGIT}|\.)* 

IllFormed_Number ({DIGIT}*\.?{DIGIT}*|\.{DIGIT}+)[Ee][+-]?{DIGIT}*\.({DIGIT}+)?
Invalid_Id_Suffix_Num_Prefix {DIGIT}+{AlphaNumeric}+
Unrecognized_Char .


RELOP "=="|"!="|"<"|"<="|">"|">="
ADDOP "+"|"-"
MULOP "*"|"/"|"%"
INCOP "++"
DECOP "--"
ASSIGNOP "="
LOGICOP "&&"|"||"
BITOP "&"|"|"|"^"|"<<"|">>" 
NOT "!"
LPAREN "("
RPAREN ")"
LCURL "{"
RCURL "}"
LSQUARE "["
RSQUARE "]"
COMMA ","
SEMICOLON ";"


%%

{WHITESPACE}    {}

{NEWLINE} { lines++;}

"if"        {
                yylval.symbol= new SymbolInfo(yytext,"IF",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "IF");
                return IF; 
            }
"else"      {
                yylval.symbol= new SymbolInfo(yytext,"ELSE",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "ELSE");

                return ELSE; 
            }
"for"       {
                yylval.symbol= new SymbolInfo(yytext,"FOR",true,lines, lines);
                showToken(lines, yytext, "FOR");
                yylval.symbol->setLeaf(true);

                return FOR; 
            }
"while"     {
                yylval.symbol= new SymbolInfo(yytext,"WHILE",true,lines, lines);
                showToken(lines, yytext, "WHILE");
                yylval.symbol->setLeaf(true);
                return WHILE; 
            }
"do"        {
                yylval.symbol= new SymbolInfo(yytext,"DO",true,lines, lines);
                showToken(lines, yytext, "DO");
                yylval.symbol->setLeaf(true);
                return DO; 
            }
"break"     {
                yylval.symbol= new SymbolInfo(yytext,"BREAK",true,lines, lines);
                showToken(lines, yytext, "BREAK");
                yylval.symbol->setLeaf(true);
                return BREAK; 
            }
"int"       {
                yylval.symbol= new SymbolInfo(yytext,"INT",true,lines, lines);
                showToken(lines, yytext, "INT");
                yylval.symbol->setLeaf(true);
                return INT; 
            }
"char"      {
                yylval.symbol= new SymbolInfo(yytext,"CHAR",true,lines, lines);
                showToken(lines, yytext, "CHAR");
                yylval.symbol->setLeaf(true);
                return CHAR; 
            }
"float"     {
                yylval.symbol= new SymbolInfo(yytext,"FLOAT",true,lines, lines);
                showToken(lines, yytext, "FLOAT");
                yylval.symbol->setLeaf(true);
                return FLOAT; 
            }
"double"    {
                yylval.symbol= new SymbolInfo(yytext,"DOUBLE",true,lines, lines);
                showToken(lines, yytext, "DOUBLE");
                yylval.symbol->setLeaf(true);
                return DOUBLE; 
            }
"void"      {
                yylval.symbol= new SymbolInfo(yytext,"VOID",true,lines, lines);
                showToken(lines, yytext, "VOID");
                yylval.symbol->setLeaf(true);
                return VOID; 
            }
"return"    {
                yylval.symbol= new SymbolInfo(yytext,"RETURN",true,lines, lines);
                showToken(lines, yytext, "RETURN");
                yylval.symbol->setLeaf(true);
                return RETURN; 
            }
"switch"    {
                yylval.symbol= new SymbolInfo(yytext,"SWITCH",true,lines, lines);
                showToken(lines, yytext, "SWITCH");
                yylval.symbol->setLeaf(true);
                return SWITCH; 
            }
"case"      {
                yylval.symbol= new SymbolInfo(yytext,"CASE",true,lines, lines);
                showToken(lines, yytext, "CASE");
                yylval.symbol->setLeaf(true);
                return CASE; 
            }
"default"   {
                yylval.symbol= new SymbolInfo(yytext,"DEFAULT",true,lines, lines);
                showToken(lines, yytext, "DEFAULT");
                yylval.symbol->setLeaf(true);
                return DEFAULT; 
            }

"printf"    {
                yylval.symbol= new SymbolInfo(yytext,"PRINTLN",true,lines, lines);
                showToken(lines, yytext, "PRINTLN");
                yylval.symbol->setLeaf(true);
                return PRINTLN; 
            }

"continue"  {
                yylval.symbol= new SymbolInfo(yytext,"CONTINUE",true,lines, lines);
                showToken(lines, yytext, "CONTINUE");
                yylval.symbol->setLeaf(true);
                return CONTINUE; 
            }

{Integer}   {
                yylval.symbol= new SymbolInfo(yytext,"CONST_INT",true,lines, lines);
                showToken(lines, yytext, "CONST_INT");
                yylval.symbol->setLeaf(true);
                return CONST_INT; 
            }

{Floating_Point}    {
    log_out<<"Line# "<<lines<< ": Token <CONST_FLOAT> Lexeme "<<yytext<<" found\n";
    yylval.symbol= new SymbolInfo(yytext,"CONST_FLOAT",true,lines, lines);
    yylval.symbol->setLeaf(true);
    showToken(lines, yytext, "CONST_FLOAT");
    return CONST_FLOAT;
}

{Too_Many_Decimal_Points}   {
    log_out<<"Error at line# "<<lines<<": TOO_MANY_DECIMAL_POINTS "<<yytext<<"\n";
    errors++; 
}
{IllFormed_Number}  {
    log_out<<"Error at line# "<<lines<<": ILLFORMED_NUMBER "<<yytext<<"\n";
    errors++;
}

{ID}    {
    yylval.symbol= new SymbolInfo(yytext,"ID",true,lines, lines);
    showToken(lines, yytext,"ID");
    return ID; 
}

{Invalid_Id_Suffix_Num_Prefix}  {
    log_out<<"Error at line# "<<lines<<": INVALID_ID_SUFFIX_NUM_PREFIX "<<yytext<<"\n";
    errors++;
}

{INCOP}     {
                yylval.symbol= new SymbolInfo(yytext,"INCOP",true,lines, lines);
                showToken(lines, yytext, "INCOP");
                return INCOP; 
            }

{DECOP}     {
                yylval.symbol= new SymbolInfo(yytext,"DECOP",true,lines, lines);
                showToken(lines, yytext, "DECOP");
                return DECOP; 
            }
{ADDOP}     {
                yylval.symbol= new SymbolInfo(yytext,"ADDOP",true,lines, lines);
                showToken(lines, yytext, "ADDOP");
                return ADDOP; 
            }
{MULOP}     {
                yylval.symbol= new SymbolInfo(yytext,"MULOP",true,lines, lines);
                showToken(lines, yytext, "MULOP");
                return MULOP; 
            }
{RELOP}     {
                yylval.symbol= new SymbolInfo(yytext,"RELOP",true,lines, lines);
                showToken(lines, yytext, "RELOP");
                return RELOP; 
            }
{ASSIGNOP}  {
                yylval.symbol= new SymbolInfo(yytext,"ASSIGNOP",true,lines, lines);
                showToken(lines, yytext, "ASSIGNOP");
                return ASSIGNOP; 
            }
{LOGICOP}   {
                yylval.symbol= new SymbolInfo(yytext,"LOGICOP",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "LOGICOP");
                return LOGICOP; 
            }
{BITOP}     {
                yylval.symbol= new SymbolInfo(yytext,"BITOP",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "BITOP");
                return BITOP; 
            }
{NOT}       {
                yylval.symbol= new SymbolInfo(yytext,"NOT",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "NOT");
                return NOT; 
            }
{LPAREN}    {
                yylval.symbol= new SymbolInfo(yytext,"LPAREN",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "LPAREN");
                return LPAREN; 
            }
{RPAREN}    {
                yylval.symbol= new SymbolInfo(yytext,"RPAREN",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "RPAREN");
                return RPAREN; 
            }
{LCURL}     {
                yylval.symbol= new SymbolInfo(yytext,"LCURL",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "LCURL");
                return LCURL; 
            }
{RCURL}     {
                yylval.symbol= new SymbolInfo(yytext,"RCURL",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "RCURL");
                return RCURL; 
            }
{LSQUARE}   {
                yylval.symbol= new SymbolInfo(yytext,"LSQUARE",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "LSQUARE");
                return LSQUARE; 
            }
{RSQUARE}   {
                yylval.symbol= new SymbolInfo(yytext,"RSQUARE",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "RSQUARE");
                return RSQUARE; 
            }
{COMMA}     {
                yylval.symbol= new SymbolInfo(yytext,"COMMA",true,lines, lines);
                showToken(lines, yytext, "COMMA");
                return COMMA; 
            }
{SEMICOLON} {
                yylval.symbol= new SymbolInfo(yytext,"SEMICOLON",true,lines, lines);
                yylval.symbol->setLeaf(true);
                showToken(lines, yytext, "SEMICOLON");
                return SEMICOLON; 
            }



\'  {
        ch1.clear(); 
        ch2.clear(); 
        BEGIN ch_State;
}
    

\"  {
        st1.clear(); 
        st2.clear();
        innerNL = 0; 
        BEGIN str_State;
}


\/\/    {
            cmnt.clear(); 
            cmnt+="//"; 
            innerNL=0; 
            BEGIN single_Comment; 
}

\/\*    {
            cmnt.clear();
            cmnt+="/*"; 
            innerNL=0; 
            BEGIN multiple_Comment; 
}

<ch_State>\\\\  ch1+="\\", ch2+="\\\\";
<ch_State>\\\'  ch1+="\'", ch2+="\\\'";
<ch_State>\\\"  ch1+="\"", ch2+="\\\"";
<ch_State>\\a   ch1+="\a", ch2+="\\a";
<ch_State>\\b   ch1+="\b", ch2+="\\b";
<ch_State>\\f   ch1+="\f", ch2+="\\f";
<ch_State>\\n   ch1+="\n", ch2+="\\n";
<ch_State>\\r   ch1+="\r", ch2+="\\r";
<ch_State>\\t   ch1+="\t", ch2+="\\t"; 
<ch_State>\\v   ch1+="\v", ch2+="\\v";
<ch_State>\\0   ch1+="\0", ch2+="\\0";


<ch_State><<EOF>>   {
    res = "'"; 
    res+= ch2;
    errors++; 
    log_out<<"'"<<ch2<<endl; 
    log_out<<"Error at line# "<<lines<<": UNFINISHED_CONST_CHAR "<<res<<"\n";
    BEGIN INITIAL; 
}



<ch_State>\'    {
    res= "'"; 
    res+=ch2; 
    res+="'"; 
    if((ll)ch1.size()==0){
        if(ch2=="\\0"){
            log_out<<"Line# "<<lines<< ": Token <" <<"CONST_CHAR"<<"> Lexeme "<<res<<" found\n";
            yylval.symbol= new SymbolInfo(yytext,"CONST_CHAR",true,lines, lines);
            yylval.symbol->setLeaf(true);
            showToken(lines, yytext, "CONST_CHAR");
            return CONST_CHAR;
        }
        else{
            errors++; 
            log_out<<"Error at line# "<<lines<<": EMPTY_CONST_CHAR "<<res<<"\n";
        }
    }
    else if((ll)ch1.size()==1){
        log_out<<"Line# "<<lines<< ": Token <" <<"CONST_CHAR"<<"> Lexeme "<<ch1<<" found\n";
        yylval.symbol= new SymbolInfo(yytext,"CONST_CHAR",true,lines, lines);
        yylval.symbol->setLeaf(true);
        showToken(lines, yytext, "CONST_CHAR");
        return CONST_CHAR;
    }
    else{
        errors++; 
        log_out<<"Error at line# "<<lines<<": MULTICHAR_CONST_CHAR "<<res<<"\n";
    }

    BEGIN INITIAL; 
}



<ch_State>[\r]?\n   {
    res = "'"; 
    res+= ch2;
    errors++; 
    log_out<<"Error at line# "<<lines<<": UNFINISHED_CONST_CHAR "<<res<<"\n";
    lines++;
    BEGIN INITIAL; 
}


<ch_State>.   {
    ch1+=yytext[0]; 
    ch2+=yytext[0];  
}

<str_State>\\\\  st1+="\\", st2+="\\\\";
<str_State>\\\'  st1+="\'", st2+="\\\'";
<str_State>\\\"  st1+="\"", st2+="\\\"";
<str_State>\\a   st1+="\a", st2+="\\a";
<str_State>\\b   st1+="\b", st2+="\\b";
<str_State>\\f   st1+="\f", st2+="\\f";
<str_State>\\n   st1+="\n", st2+="\\n";
<str_State>\\r   st1+="\r", st2+="\\r";
<str_State>\\t   st1+="\t", st2+="\\t";
<str_State>\\v   st1+="\v", st2+="\\v";
<str_State>\\0   st1+="\0", st2+="\\0";

<str_State>\\\r\n   {
    innerNL++;
    st2+="\\\r\n";
    // st2+="\t";
    BEGIN multi_str_State; 
}
<str_State>\\\n   {
    innerNL++;
    st2+="\\\n";
    // st2+="\t"; 
    BEGIN multi_str_State; 
}


<str_State>[\r]?\n  {
    res.clear();
    res = "\""; 
    res+=st2; 
    innerNL++;
    errors++;
    
    log_out<<"Error at line# "<<lines<<": UNFINISHED_STRING "<<res<<"\n";
    lines+= innerNL; 
    innerNL=0; 
    BEGIN INITIAL;
}

<str_State><<EOF>>  {
    errors++;
    
    res="\""; 
    res+=st2; 
    log_out<<"Error at line# "<<lines<<": UNFINISHED_STRING "<<res<<"\n";
    lines+= innerNL;
    innerNL=0; 
    BEGIN INITIAL;
}

<str_State>\"  {
    res.clear();
    res = "\""; 
    res+=st2; 
    res+="\""; 
 
    log_out<<"Line# "<<lines<< ": Token <" <<"SINGLE LINE STRING"<<"> Lexeme "<<res<<" found\n";
    lines+= innerNL; 
    innerNL=0; 
    yylval.symbol= new SymbolInfo(yytext,"SINGLE_LINE_STRING", true, lines, lines);
    yylval.symbol->setLeaf(true);
    showToken(lines, yytext, "SINGL_LINE_STRING");
    return SINGLE_LINE_STRING;
    BEGIN INITIAL; 
}

<str_State>.  {
    st1+=yytext[0];
    st2+=yytext[0]; 
}


<multi_str_State>\\\\  st1+="\\", st2+="\\\\";
<multi_str_State>\\\'  st1+="\'", st2+="\\\'";
<multi_str_State>\\\"  st1+="\"", st2+="\\\"";
<multi_str_State>\\a   st1+="\a", st2+="\\a";
<multi_str_State>\\b   st1+="\b", st2+="\\b";
<multi_str_State>\\f   st1+="\f", st2+="\\f";
<multi_str_State>\\n   st1+="\n", st2+="\\n";
<multi_str_State>\\r   st1+="\r", st2+="\\r";
<multi_str_State>\\t   st1+="\t", st2+="\\t";
<multi_str_State>\\v   st1+="\v", st2+="\\v";
<multi_str_State>\\0   st1+="\0", st2+="\\0";




<multi_str_State>\\\r\n   {
    innerNL++;
    st2+="\\\r\n"; 
    // st2+="\t";
}

<multi_str_State>\\\n   {
    innerNL++;
    st2+="\\\n";
    // st2+="\t";
}

<multi_str_State>[\r]?\n  {
    res.clear();
    res = "\""; 
    res+=st2; 
    errors++;
    lines+= innerNL;
    log_out<<"Error at line# "<<lines<<": UNFINISHED_STRING "<<res<<"\n";
    lines++;
    innerNL=0; 
    BEGIN INITIAL;
}

<multi_str_State><<EOF>>  {
    errors++;
    lines+= innerNL;
    res="\""; 
    res+=st2; 
    log_out<<"Error at line# "<<lines<<": UNFINISHED_STRING "<<res<<"\n";
    
    innerNL=0; 
    BEGIN INITIAL;
}


<multi_str_State>\" {
    res.clear();
    res = "\""; 
    res+=st2; 
    res+="\"";  
    log_out<<"Line# "<<lines<< ": Token <" <<"MULTI LINE STRING"<<"> Lexeme "<<res<<" found\n";
    lines+= innerNL; 
    innerNL=0; 
     
    yylval.symbol= new SymbolInfo(yytext,"MULTI_LINE_STRING");
    yylval.symbol->setLeaf(true);
    showToken(lines, yytext, "MULTI_LINE_STRING");
    return MULTI_LINE_STRING;
    BEGIN INITIAL;
}

<multi_str_State>.  {
    st1+=yytext[0];
    st2+=yytext[0]; 
}

<single_Comment>\\\r\n  {
    innerNL++;
    cmnt+="\\\r\n";
}

<single_Comment>\\\n    {
    innerNL++; 
    cmnt+="\\\n"; 
}
<single_Comment>[\r]?\n {
    innerNL++; 
    log_out<<"Line# "<<lines<< ": Token <SINGLE LINE COMMENT> Lexeme "<<cmnt<<" found\n";
    lines+= innerNL; 
    innerNL=0; 
    BEGIN INITIAL;
}
<single_Comment><<EOF>> {
    log_out<<"Line# "<<lines<< ": Token <SINGLE LINE COMMENT> Lexeme "<<cmnt<<" found\n";
    lines+= innerNL; 
    innerNL=0; 
    BEGIN INITIAL;
}

<single_Comment>\\  {
    cmnt+="\\"; 
}
<single_Comment>.   {
    cmnt+=yytext[0];
}

<multiple_Comment>\*\/  {
    cmnt+="*/";
    log_out<<"Line# "<<lines<< ": Token <MULTI LINE COMMENT> Lexeme "<<cmnt<<" found\n";
    lines+= innerNL; 
    innerNL=0; 
    BEGIN INITIAL;
}

<multiple_Comment><<EOF>>   { 
    errors++;
    lines+= innerNL; 
    log_out<<"Error at line# "<<lines<<": UNFINISHED_COMMENT "<<cmnt<<"\n";
    innerNL=0; 
    BEGIN INITIAL;
}

<multiple_Comment>\r    {
    cmnt+="\r";
}
<multiple_Comment>\n    {
    cmnt+="\n"; 
    innerNL++;
}
<multiple_Comment>. {
    cmnt+=yytext[0]; 
}


{Unrecognized_Char} {
    log_out<<"Error at line# "<<lines<<": UNRECOGNIZED_CHAR "<<yytext<<"\n";
    errors++;
}


%%

