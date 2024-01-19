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
#include"Symbol_Table.h" 
#define ll long long int
#include <sstream>
using namespace std;


string st1; // exact char print          
string st2; // /t /a / 
string ch1;
string ch2;
string res; // "string"
string cmnt; 

ll lines = 1; 
ll errors = 0; 
ll innerNL = 0; 

char ch; 

bool completed = true; 

ofstream token_out; 
ofstream log_out; 

SymbolTable* symbolTable = new SymbolTable(10); 

void showKeyWord(string token, string lexeme , ll lineNo){
    token_out<<"<"<<token<<", "<<lexeme<<">\n"; 
    log_out<<"Line# "<<lineNo<< ": Token <" <<token<<"> Lexeme "<<lexeme<<" found\n";     
}
void showOperator(string token, string lexeme, ll lineNo){
    token_out<<"<"<<token<<", "<<lexeme<<">\n"; 
    log_out<<"Line# "<<lineNo<< ": Token <" <<token<<"> Lexeme "<<lexeme<<" found\n";
    if(lexeme=="{"){
        symbolTable->enter_scope(); 
    }
    else if(lexeme=="}"){
        symbolTable->exit_scope(); 
    }
}

void showID(string token, string lexeme, ll lineNo){
    token_out<<"<"<<token<<", "<<lexeme<<">\n"; 
    log_out<<"Line# "<<lineNo<< ": Token <" <<token<<"> Lexeme "<<lexeme<<" found\n";

    bool hasInserted = symbolTable->Insert(SymbolInfo(lexeme,token));
    if(hasInserted){
        symbolTable->print_all_scopes(log_out); 
    }
    else{
        log_out<<"\t"<<lexeme<<" already exists in the current ScopeTable\n"; 
    }
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
Too_Many_Decimal_Points {DIGIT}*\.{DIGIT}+\.({DIGIT}|\.)* 

IllFormed_Number ({DIGIT}*\.?{DIGIT}*|\.{DIGIT}+)[Ee][+-]?{DIGIT}*\.({DIGIT}+)?
Invalid_Id_Suffix_Num_Prefix {DIGIT}+{AlphaNumeric}+
Unrecognized_Char .


RELOP "=="|"!="|"<"|"<="|">"|">="
ADDOP "+"|"-"
MULOP "*"|"/"|"%"
INCOP "++"|"--"
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


{NEWLINE} {lines++;}

"if"        {showKeyWord("IF", yytext, lines);}
"else"      {showKeyWord("ELSE", yytext, lines);}
"for"       {showKeyWord("FOR", yytext, lines);}
"while"     {showKeyWord("WHILE", yytext, lines);}
"do"        {showKeyWord("DO", yytext, lines);}
"break"     {showKeyWord("BREAK", yytext, lines);}
"int"       {showKeyWord("INT", yytext, lines);}
"char"      {showKeyWord("CHAR", yytext, lines);}
"float"     {showKeyWord("FLOAT", yytext, lines);}
"double"    {showKeyWord("WHILE", yytext, lines);}
"void"      {showKeyWord("VOID", yytext, lines);}
"return"    {showKeyWord("RETURN", yytext, lines);}
"switch"    {showKeyWord("SWITCH", yytext, lines);}
"case"      {showKeyWord("CASE", yytext, lines);}
"default"   {showKeyWord("DEFAULT", yytext, lines);}
"continue"  {showKeyWord("CONTINUE", yytext, lines);}

{Integer}   {
    token_out<<"<"<<"CONST_INT"<<", "<<yytext<<">\n"; 
    log_out<<"Line# "<<lines<< ": Token <CONST_INT> Lexeme "<<yytext<<" found\n";
}

{Floating_Point}    {
    token_out<<"<"<<"CONST_FLOAT"<<", "<<yytext<<">\n"; 
    log_out<<"Line# "<<lines<< ": Token <CONST_FLOAT> Lexeme "<<yytext<<" found\n";
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
    showID("ID", yytext, lines); 
}

{Invalid_Id_Suffix_Num_Prefix}  {
    log_out<<"Error at line# "<<lines<<": INVALID_ID_SUFFIX_NUM_PREFIX "<<yytext<<"\n";
    errors++;
}

{INCOP}     {showOperator("INCOP", yytext, lines);}
{ADDOP}     {showOperator("ADDOP", yytext, lines);}
{MULOP}     {showOperator("MULOP", yytext, lines);}
{RELOP}     {showOperator("RELOP", yytext, lines);}
{ASSIGNOP}  {showOperator("ASSIGNOP", yytext, lines);}
{LOGICOP}   {showOperator("LOGICOP", yytext, lines);}
{BITOP}     {showOperator("BITOP", yytext, lines);}
{NOT}       {showOperator("NOT", yytext, lines);}
{LPAREN}    {showOperator("LPAREN", yytext, lines);}
{RPAREN}    {showOperator("RPAREN", yytext, lines);}
{LCURL}     {showOperator("LCURL", yytext, lines);}
{RCURL}     {showOperator("RCURL", yytext, lines);}
{LSQUARE}   {showOperator("LSQUARE", yytext, lines);}
{RSQUARE}   {showOperator("RSQUARE", yytext, lines);}
{COMMA}     {showOperator("COMMA", yytext, lines);}
{SEMICOLON} {showOperator("SEMICOLON", yytext, lines);}



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
            token_out<<"<CONST_CHAR, "<<ch1<<">\n";
            log_out<<"Line# "<<lines<< ": Token <" <<"CONST_CHAR"<<"> Lexeme "<<res<<" found\n";
        }
        else{
            errors++; 
            log_out<<"Error at line# "<<lines<<": EMPTY_CONST_CHAR "<<res<<"\n";
        }
    }
    else if((ll)ch1.size()==1){
        token_out<<"<CONST_CHAR, "<<ch1<<">\n";
        log_out<<"Line# "<<lines<< ": Token <" <<"CONST_CHAR"<<"> Lexeme "<<ch1<<" found\n";
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

    token_out<<"<SINGLE LINE STRING, "<<st1<<">"<<endl; 
    log_out<<"Line# "<<lines<< ": Token <" <<"SINGLE LINE STRING"<<"> Lexeme "<<res<<" found\n";
    lines+= innerNL; 
    innerNL=0; 
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

    token_out<<"<MULTI LINE STRING, "<<st1<<">"<<endl; 
    log_out<<"Line# "<<lines<< ": Token <" <<"MULTI LINE STRING"<<"> Lexeme "<<res<<" found\n";
    lines+= innerNL; 
    innerNL=0; 
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

    token_out.open("1905095_token.txt"); 
    log_out.open("1905095_log.txt"); 
    yyin = fin; 
    yylex();

    symbolTable->print_all_scopes(log_out); 

    log_out<<"Total lines: "<<lines<<endl; 
    log_out<<"Total errors: "<<errors; 

    fclose(yyin);
    token_out.close();
    log_out.close();

    return 0; 
}