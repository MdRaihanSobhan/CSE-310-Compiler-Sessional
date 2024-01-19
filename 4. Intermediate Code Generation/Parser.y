%{
#include<iostream>
#include<stdio.h>
#include<cstring>
#include <set>
#define ll long long int
#include <sstream>
#include <stdlib.h>
#include<string>
#include "Symbol_Table.cpp" 
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



%}

%union  {
    SymbolInfo* symbol; 
}

%token <symbol> ADDOP MULOP INCOP RELOP ID CONST_INT CONST_FLOAT IF ELSE FOR WHILE DO BREAK CHAR FLOAT DOUBLE VOID RETURN CONTINUE PRINTLN ASSIGNOP LOGICOP NOT LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON DECOP INT SWITCH CASE DEFAULT BITOP CONST_CHAR SINGLE_LINE_STRING MULTI_LINE_STRING

%type <symbol> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments IF_Block
%nonassoc LOWER_THAN_ELSE 
%nonassoc ELSE

%%

start :{

    code_out<<".MODEL SMALL\n.STACK 100h\n.DATA\n\tCR EQU 0DH\n\tLF EQU 0AH\n\tnumber DB \"00000\$\"\n\t"<<endl; 
    temp_out<<".CODE\n";

}     program
	{
		$$=new SymbolInfo($2->getName(),"start");
        debugString+=$2->getName(); 
		showRule("start : program");
		log_out<<"Total lines: "<<lines<<endl;
		log_out<<"Total errors: "<<errors<<endl;
        $$->addChild($2);
        $$->setStartLine($2->getStartLine()); 
        $$->setEndLine($2->getEndLine()); 
        showParseTree($$,0);     

        genPrintfunction();    
        gen_asm_file(); 
	} 
	;

program:    program unit	
    {
        showRule("program : program unit");
        $$=new SymbolInfo($1->getName()+" "+$2->getName(),"program");
        debugString+=$1->getName(); 
        $$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine()); 
	}
	|   unit	
    {
        showRule("program : unit");
        $$=new SymbolInfo($1->getName(),"program");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine()); 
	}
	;

	
unit:   var_declaration	
    {
        $$=new SymbolInfo($1->getName(),"unit");
        showRule("unit : var_declaration");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        debugString+=$1->getName(); 
        debugGetType+=$1->getType(); 

	}
    
    |   func_declaration	
    {
        $$=new SymbolInfo($1->getName(),"unit");
		showRule("unit : func_declaration");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
	}
    |   func_definition	
    {
        $$=new SymbolInfo($1->getName(),"unit");
		showRule("unit : func_definition");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
    }
    ;


func_declaration:   type_specifier ID LPAREN parameter_list RPAREN {
		running_function = $2->getName();
        debugString+=$1->getName(); 
		if(symbolTable->lookUp(running_function) == NULL){
			SymbolInfo* temp = new SymbolInfo(running_function, $1->getName());
			for(auto i : parameter_list){
				temp->addParameter(i);
                error_out<<"Parameter added "<<endl;
			}
			temp->setData_type($1->getName());
			temp->setStructure_type("func");
            temp->setType($1->getType()); 
			parameter_list.clear();
			symbolTable->InsertFunc(*temp);
		}
		else{
            error_out<<"Line# "<<lines<<": Redefinition of '"+running_function<<"'"<<endl; 
            errors++; 			
		}
        running_function = $2->getName();

	} SEMICOLON	{
        showRule("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
        string symName = $1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$7->getName()+"\n";
        $$ = new SymbolInfo(symName, "func_declaration");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        $$->addChild($7);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($7->getEndLine());
	}

    |   type_specifier ID LPAREN RPAREN {
			running_function=$2->getName();
			if(symbolTable->lookUp(running_function) == NULL){
				SymbolInfo* temp = new SymbolInfo(running_function, $1->getType());
                debugGetType+=$1->getType(); 
				temp->setStructure_type("func");
				temp->setData_type($1->getName());
				symbolTable->InsertFunc(*temp);
			}
			else{
                error_out<<"Line# "<<lines<<": Redeclaration of "+running_function<<endl; 
                errors++;				
			}
		} SEMICOLON	{
            showRule("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
            string symName = $1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$6->getName()+"\n";
            $$ = new SymbolInfo(symName, "func_declaration");
            $$->addChild($1);
            $$->addChild($2);
            $$->addChild($3);
            $$->addChild($4);
            $$->addChild($6);
            $$->setStartLine($1->getStartLine()); 
            $$->setEndLine($6->getEndLine());
		}
    ;


func_definition: type_specifier ID LPAREN parameter_list RPAREN {

    gen_func_begin($2->getName());

	running_function=$2->getName();
    debugString+=$1->getName(); 
    debugGetType+=$1->getType(); 
    
    SymbolInfo* temp = symbolTable->lookUp(running_function);

	if(temp == NULL){
		temp = new SymbolInfo(running_function,"FUNCTION" );

		for(auto i : parameter_list){
			temp->addParameter(i);
            error_out<<"Parameter added"<<endl; 
		}
		temp->setStructure_type("func");
		temp->setData_type($1->getName());
		symbolTable->InsertFunc(*temp);
       

	}
	else{
		if(temp->getStructure_type() == "func"){
            error_out<<"Line# "<<lines<<": Redeclaration of "+running_function<<endl; 
            errors++;
		}
		else{
			vector<SymbolInfo> vec_temp = temp->getParameterList();
			if($1->getName() != temp->getData_type()){
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
	
} compound_statement	{

    gen_func_end($2->getName());


    showRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
    string symName = $1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$7->getName();
    debugString+=$1->getName(); 
    $$ = new SymbolInfo(symName, "func_definition");	
    $$->addChild($1);
    $$->addChild($2);
    $$->addChild($3);
    $$->addChild($4);
    $$->addChild($5);
    $$->addChild($7);
    $$->setStartLine($1->getStartLine()); 
    $$->setEndLine($7->getEndLine());
    }
    | type_specifier ID LPAREN RPAREN {

        gen_func_begin($2->getName());


        running_function=$2->getName();
        if(symbolTable->lookUp(running_function) == NULL){
            SymbolInfo* temp = new SymbolInfo(running_function, $1->getType());
            
            temp->setStructure_type("func");
            temp->setData_type($1->getName());
            symbolTable->InsertFunc(*temp);
        }
        else{
            SymbolInfo* temp = symbolTable->lookUp(running_function);
            if(temp->getStructure_type() == "func_dec"){
                error_out<<"Line# "<<lines<<":  Redeclaration of function "+running_function<<endl; 
                errors++;	
            }
        }
        running_function = $2->getName();

			
	} compound_statement	{

        gen_func_end($2->getName());

        showRule("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
        string symName = $1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$6->getName();
        $$ = new SymbolInfo(symName, "func_definition");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($6);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($6->getEndLine());
	}
 	;				



parameter_list:     parameter_list COMMA type_specifier ID
    {
        showRule("parameter_list  : parameter_list COMMA type_specifier ID");
		$$=new SymbolInfo($1->getName()+$2->getName()+$3->getName()+" "+$4->getName(),"parameter_list");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($4->getEndLine());

        SymbolInfo* temp = new SymbolInfo($4->getName(), $4->getType());
        temp->setStructure_type("var");

        $$->setData_type($1->getData_type()); 

        $3->setData_type($3->getName()); 


        temp->setData_type($3->getName());


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
    |   parameter_list COMMA type_specifier 
    {
        showRule("parameter_list  : parameter_list COMMA type_specifier");
        string symName = $1->getName()+" "+$2->getName()+" "+$3->getName();

        $$ = new SymbolInfo(symName, "parameter_list");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
        SymbolInfo* temp = new SymbolInfo($3->getName(), $3->getType());
        temp->setStructure_type("var");
        temp->setData_type($3->getName());
        $3->setData_type($3->getName()); 
        $$->setData_type($1->getData_type()); 


        
        parameter_list.push_back(*temp);
    }
    |   type_specifier ID
    {
        showRule("parameter_list  : type_specifier ID");
        string symName = $1->getName()+" "+$2->getName();

        $$ = new SymbolInfo(symName, "type_specifier");
        $$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
        SymbolInfo* temp = new SymbolInfo($2->getName(), $2->getType());
        $1->setData_type($1->getName()); 
        temp->setStructure_type("var");
        temp->setData_type($1->getName());


        $1->setData_type($1->getName()); 
        $$->setData_type($1->getName()); 


        parameter_list.push_back(*temp);
    }
    |   type_specifier
    {
        showRule("parameter_list  : type_specifier");
        string symName = $1->getName();
        $$ = new SymbolInfo(symName, "parameter_list");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        SymbolInfo* temp = new SymbolInfo($1->getName(), $1->getType());
        temp->setStructure_type("var");
        temp->setData_type($1->getName());

        $1->setData_type($1->getName()); 
        $$->setData_type($1->getName()); 

        parameter_list.push_back(*temp);
    }
    ;

compound_statement:     LCURL { 
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
    
    } statements RCURL
    {
        $$=new SymbolInfo($1->getName()+"\n"+$3->getName()+"\n"+$4->getName()+"\n","compound_statement");
        $$->addChild($1);
        $$->addChild($3);
        $$->addChild($4);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($4->getEndLine());

		showRule("compound_statement:   LCURL statements RCURL");
        symbolTable->print_all_scopes(log_out);
        symbolTable->exit_scope(); 
    }
    |   LCURL {
        symbolTable->enter_scope(); 
        
        if(parameter_list.size() != 0){
            for(auto i : parameter_list){
                symbolTable->Insert(i);
            }
        }
        parameter_list.clear();
    } RCURL
    {
        $$=new SymbolInfo($1->getName()+$3->getName(),"compound_statement");
        $$->addChild($1);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
		showRule("compound_statement:   LCURL RCURL");
        symbolTable->exit_scope(); 
        symbolTable->print_all_scopes(log_out); 

    }
    ;

var_declaration:    type_specifier declaration_list SEMICOLON	
    {
    	$$=new SymbolInfo($1->getName()+" "+$2->getName()+$3->getName(),"var_declaration");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
        
        $$->setData_type($1->getName()); 

		showRule("var_declaration : type_specifier declaration_list SEMICOLON");
        if($1->getName() == "void"){
            error_out<<"Line# "<<lines<<": Variable or field '"<<$1->getName()<<"' declared void"<<endl; 
            errors++;
		}
	}
 	;

// done

type_specifier:     INT	
    {
        $$=new SymbolInfo("int","type_specifier");
        $$->addChild($1);
        debugString+=$1->getName(); 
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type("int"); 
		showRule("type_specifier	: INT");
        curr_type="int"; 
	}
 	|   FLOAT	    
    {
        $$=new SymbolInfo("float","type_specifier");
        $$->addChild($1); 
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type("float"); 
    	showRule("type_specifier	: FLOAT");
        curr_type= "float"; 
				
	}
 	|   VOID
    {
        $$=new SymbolInfo("void","type_specifier");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type("void"); 
		showRule("type_specifier	: VOID");
        curr_type="void"; 
	}
 	;
 		
declaration_list:   declaration_list COMMA ID	
    {
		showRule("declaration_list : declaration_list COMMA ID");
		$$=new SymbolInfo($1->getName()+$2->getName()+$3->getName(),"declaration_list");

        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
                
        SymbolInfo* temp = new SymbolInfo($3->getName(), $3->getType());
        temp->setStructure_type("var");
        temp->setData_type(curr_type); 

        ScopeTable* forErrorCheck = symbolTable->getCurrent_scope();
                        
        SymbolInfo* toInsert =  forErrorCheck->lookUp(temp->getName());

        if(toInsert!=NULL){
            error_out<<"Line# "<<lines<<": Redeclaration of "+ temp->getName()<<endl; 
            errors++;
        }

        if(isGlobal()==1){
            temp->setIcg_name($3->getName()); 
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

 	|   declaration_list COMMA ID LSQUARE CONST_INT RSQUARE	
    {
		showRule("declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName(),"declaration_list");
        
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        $$->addChild($6);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($6->getEndLine());
        SymbolInfo* temp = new SymbolInfo($3->getName(), $3->getType());
        temp->setStructure_type("array");
        temp->setData_type(curr_type);

        ScopeTable* forErrorCheck = symbolTable->getCurrent_scope();
        if(forErrorCheck->lookUp(temp->getName())!=NULL){
            error_out<<"Line# "<<lines<<": Redeclaration of "+ temp->getName()<<endl; 
            errors++;
        }

        ll array_size = stoi($5->getName());
        temp->setArr_size(array_size);

        if(isGlobal()==true){
            temp->setIcg_name($3->getName()); 
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

 	|   ID	
    {
        $$=new SymbolInfo($1->getName(),"declaration_list");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
		showRule("declaration_list : ID");
        debugGetType+=$1->getType(); 
        // parse_out<<debugGetType<<endl; 

        SymbolInfo* temp = new SymbolInfo($1->getName(), $1->getType());
        temp->setStructure_type("var");
        temp->setData_type(curr_type);

        ScopeTable* forErrorCheck = symbolTable->getCurrent_scope();
        if(symbolTable->lookUpCurrentScope(temp->getName())!=NULL){
            error_out<<"Line# "<<lines<<": Redeclaration of "+ temp->getName()<<endl; 
            errors++;
        }
        // global scope 
        if(isGlobal()==true){
            temp->setIcg_name($1->getName()); 
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
 	|   ID LSQUARE CONST_INT RSQUARE	
    {
    	$$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName(),"declaration_list");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($4->getEndLine());
        debugString+=$1->getName(); 
        showRule("declaration_list : ID LSQUARE CONST_INT RSQUARE");
        SymbolInfo* temp = new SymbolInfo($1->getName(), $1->getType());
        temp->setStructure_type("array");
        temp->setData_type(curr_type);
        
        ScopeTable* forErrorCheck = symbolTable->getCurrent_scope();
        if(forErrorCheck->lookUp(temp->getName())!=NULL){
            
        error_out<<"Line# "<<lines<<": Redeclaration of "+ temp->getName()<<endl; 
        errors++;        
        }		

        ll array_size = stoi($3->getName());
        temp->setArr_size(array_size); 


        if(isGlobal()==true){
            if(temp->getStructure_type()== "array"){
                code_out<<"\t"<<temp->getName()<<" DW "<<temp->getArr_size()<< " DUP (0000H)"<<endl; 
                temp->setIcg_name($1->getName()); 
                symbolTable->Insert(*temp);
            }
            else{
                code_out<<"\t"<<temp->getName()<<" DW 1 DUP (0000H)"<<endl; 
                temp->setIcg_name($1->getName()); 
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
 	;
    
statements:     statement
    {
        $$=new SymbolInfo($1->getName(),"statements");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type($1->getData_type()); 

        showRule("statements:     statement"); 
    }
    |   statements statement
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName(),"statements");
        $$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
        $$->setData_type($1->getName()); 

        showRule("statements:   statements statement"); 
    }
    ;

statement:  var_declaration
    {
        $$=new SymbolInfo($1->getName(),"statement");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        showRule("statement:  var_declaration");
        $$->setData_type($1->getData_type()); 

        
    }
    |   expression_statement
    {
        $$=new SymbolInfo($1->getName(),"statement");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        showRule("statement:    expression_statement"); 
        $$->setData_type($1->getData_type()); 
        genCode("\t\tPOP AX");
        comment_out("evaluated expression: "+$1->getName());


    }
    |   compound_statement
    {
        $$=new SymbolInfo($1->getName(),"statement");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type($1->getData_type()); 
        showRule("statement:    compound_statement"); 
    }
    |   FOR LPAREN  {
        comment_out("for loop starts here"); 
        comment_out("initializing iterator variable"); 
        for_levels.clear(); 
    } expression_statement  {
        for_levels["condition"] = newLabel("CONDITION");
		for_levels["statement"] = newLabel("STATEMENT");
		for_levels["inc_dec"] = newLabel("INC_DEC");
		for_levels["end_for"] = newLabel("END_FOR");

		genCode("\t\tPOP AX");
        comment_out(" initialization of iterator done for for_loop, expression: "+$4->getName()+"\n");
        
        comment_out("Now condition check for for_loop begins"); 
		genCode("\t\t"+for_levels["condition"]+":"); 

    } expression_statement  {
        genCode("\t\tPOP AX"); 
		genCode("\t\tCMP AX, 0");
        comment_out("Break for loop");
		genCode("\t\tJE "+for_levels["end_for"]); 

        comment_out("execute statement ");

		genCode("\t\tJMP "+for_levels["statement"]);

        comment_out("increment or decrement of iterator variable");
		genCode("\t\t"+for_levels["inc_dec"]+":");

    } expression    {
        genCode("\t\tPOP AX");
        comment_out("Increment or Decrement done for expression: "+$8->getName()+"\n");

        comment_out("continue loop, again goes for condition check"); 
		genCode("\t\tJMP "+for_levels["condition"]);

        comment_out("statement of for loop starts");
		genCode("\t\t"+for_levels["statement"]+":");

    } RPAREN statement
    {

		$$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$4->getName()+" "+$6->getName()+" "+$8->getName()+" "+$10->getName()+" "+$11->getName(),"statement");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($4);
        $$->addChild($6);
        $$->addChild($8);
        $$->addChild($10);
        $$->addChild($11);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($11->getEndLine());
        showRule("statement:    FOR LPAREN expression_statement expression_statement expression RPAREN statement");

        comment_out("Jump to increment or decrement state"); 
        genCode("\t\tJMP "+for_levels["inc_dec"]);

        comment_out("For Loop ends here"); 

        comment_out("Ending block for for_loop"); 
		genCode("\t\t"+for_levels["end_for"]+":"); 
    }


    |   IF_Block %prec LOWER_THAN_ELSE
    {
        $$=new SymbolInfo($1->getName(),"statement");
		$$->addChild($1);

        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        showRule("statement:    IF LPAREN expression RPAREN statement");



        genCode("\t\t"+$1->get_label()+":\n");
    }

    |   IF_Block  ELSE  {
        comment_out("Else block begins ");
        string label = newLabel("END_ELSE");
		genCode("\t\tJMP "+label); 
		genCode("\t\t"+$1->get_label()+":\n");
		$1->set_label(label);
    } statement
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$4->getName(),"statement");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($4);
        
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($4->getEndLine());
               
        comment_out("Else block ends");
        genCode("\t\t"+$1->get_label()+":\n");


        showRule("statement:    IF LPAREN expression RPAREN statement ELSE statement");
    }

    |   WHILE LPAREN    {
        
        comment_out("while loop starts here"); 

        label_begin = newLabel("WHILE");
		genCode("\t"+label_begin+":");
    } expression RPAREN    {

        comment_out("While block begins..."); 
		string label_end = newLabel("END_WHILE");
		genCode("\t\tPOP AX");
        comment_out($4->getName()+ " loaded"); 
		genCode("\t\tCMP AX,0");
		genCode("\t\tJE "+label_end);
		$4->set_label(label_begin+" "+label_end);
    } statement
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$4->getName()+" "+$5->getName()+" "+$7->getName(),"statement");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($4);
        $$->addChild($5);
        $$->addChild($7);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($7->getEndLine());

        stringstream ss($4->get_label());
		string a, b;
		ss >> a >> b;
		genCode("\t\tJMP "+a);
		genCode("\t"+b+":\n");

        showRule("statement:    WHILE LPAREN expression RPAREN statement");
    }

    |   PRINTLN LPAREN ID RPAREN SEMICOLON
    {
		$$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+"\n","statement");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($5->getEndLine());

        showRule("statement:    PRINTLN LPAREN ID RPAREN SEMICOLON");
		SymbolInfo* lookedUp=symbolTable->lookUp($3->getName());
		if(lookedUp==NULL){
            error_out<<"Line# "<<lines<<": Undeclared variable "<<$3->getName()<<endl;
            errors++; 
		}
        else{
            error_out<<lookedUp->getIcg_name()<<endl;
            comment_out("println("+$3->getName()+")"); 

            string tempSt= "\t\tMOV AX, "+lookedUp->getIcg_name(); 
			genCode(tempSt);
            comment_out($3->getName()+" loaded"); 
			genCode("\t\tCALL print_output");
            genCode("\t\tCALL new_line");
        }
    }
    |   RETURN expression SEMICOLON
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName(),"statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
		showRule("statement:    RETURN expression SEMICOLON");
        if(is_main_func==false){

			genCode("\t\tPOP AX");
            comment_out($2->getName()+ " loaded"); 
			genCode("\t\tMOV [BP+4], AX"); 

            comment_out("Removing all internal variables from stack"); 
			genCode("\t\tADD SP, "+to_string(symbolTable->get_no_of_vars()*2));

			genCode("\t\tPOP BP"); 	
			genCode("\t\tRET"); 
        }
    }
    ;


IF_Block:   IF LPAREN expression RPAREN
    {        
        string label = newLabel("END_IF");

        $3->set_label(label); 
        
        genCode("\t\tPOP AX");
        comment_out($3->getName()+ " loaded"); 
        genCode("\t\tCMP AX, 0");

        comment_out("If block begins"); 
        genCode("\t\tJE "+label);

    } statement {
        
        comment_out("If block ends"); 
        $$= new SymbolInfo($1->getName()+" "+ $2->getName()+ " "+ $3->getName()+ " "+ $4->getName()+ " "+ $6->getName(), "IF_Block"); 
        $$->set_label($3->get_label()); 

        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4); 
        $$->addChild($6); 
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($6->getEndLine());
    }
    ;


expression_statement:   SEMICOLON
    {
		$$ = new SymbolInfo($1->getName()+"\n","expression_statement");
		showRule("expression_statement:   SEMICOLON");
        comment_out("1 for infinite loop");
		genCode("\t\tPUSH 1");
    }
    |   expression SEMICOLON
    {


		$$=new SymbolInfo($1->getName()+$2->getName()+"\n","expression_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
        $$->setData_type($1->getData_type()); 

		showRule("expression_statement:   expression SEMICOLON");
    }
    ;

variable:   ID
    {
        showRule("variable: ID"); 
		SymbolInfo* lookedUp =symbolTable->lookUp($1->getName());
        bool errorflag = false;
        string errorMessage;
        $$->setData_type($1->getData_type()); 
        if(lookedUp==NULL){
            errorflag = true;
            errorMessage= "Undeclared variable "+$1->getName();
            $$ = new SymbolInfo($1->getName(),"variable");
            $$->addChild($1);
            $$->setStartLine($1->getStartLine()); 
            $$->setEndLine($1->getEndLine());
            $$->setStructure_type("var");
            $$->setData_type("undefined"); 
        }
        else{
                if(lookedUp->getStructure_type()=="array"){
                    errorflag = true; 
                    errorMessage=lookedUp->getName()+ " is an array"; 
                }
                
                $$ = new SymbolInfo($1->getName(),"variable");
                $$->addChild($1);
                $$->setStartLine($1->getStartLine()); 
                $$->setEndLine($1->getEndLine());
                $$->setStructure_type($1->getStructure_type());
                $$->setData_type($1->getData_type());
                $$->setIcg_name(lookedUp->getIcg_name()); 
        }

        if(errorflag==true){
            error_out<<"Line# "<<lines<<":  "<<errorMessage<<endl;
            errors++; 
        }
        else{
            $$->setStructure_type(lookedUp->getStructure_type());
            $$->setData_type(lookedUp->getData_type());
        }
    }
    |   ID LSQUARE expression RSQUARE
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName(),"variable");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($4->getEndLine());
        

        showRule("variable: ID LSQUARE expression RSQUARE");
        SymbolInfo* lookedUp =symbolTable->lookUp($1->getName());
        bool errorflag = false;
        string errorMessage;
        if(lookedUp==NULL){
            errorMessage= "Undeclared variable "+ $1->getName(); 
            errorflag= true; 
            $$->setStructure_type("arrray");
            $$->setData_type("undefined"); 
            
        }
        else {
            $$->setStructure_type("array"); 
            $$->setData_type(lookedUp->getData_type());            
            
            if($3->getData_type().compare("int")!=0){
                string emessage= "Array subscript is not an integer"; 
                error_out<<"Line# "<<lines<<": "<<emessage<<endl;
                errors++; 
            }

            $1->copy_symbol(*lookedUp);
            
            comment_out($$->getName()); 
            comment_out("Popping index "+$4->getName()+" of the array "+$1->getName()); 
			genCode("\t\tPOP AX");
            comment_out("Multiplying by 2 , returns offset"); 
			genCode("\t\tSHL AX, 1");
            comment_out("Array base address"); 
			genCode("\t\tLEA BX, "+lookedUp->getIcg_name());
			genCode("\t\tSUB BX, AX");
			genCode("\t\tPUSH BX");
			$1->setIcg_name("[BX]");
            $$->setIcg_name($1->getIcg_name()); 
        }


        if(errorflag==true){
            error_out<<"Line# "<<lines<<": "<<errorMessage<<endl;
            errors++; 
        }
    }
    ;

expression:     logic_expression
    {
        $$=new SymbolInfo($1->getName(),"expression");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
		$$->setData_type($1->getData_type());
		$$->setStructure_type($1->getStructure_type());
        showRule("expression:     logic_expression"); 
        debugString+=$1->getName(); 
    }
    |   variable ASSIGNOP logic_expression
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName(),"expression");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
        showRule("expression:   variable ASSIGNOP logic_expression"); 
		if($1->getData_type().compare("undefined")!=0 && $3->getData_type().compare("undefined")!=0){
            if($1->getData_type().compare("void")==0 || $3->getData_type().compare("void")==0 ){
                error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
                errors++;
            }
        }
		
        comment_out($$->getName()); 
		$$->setData_type("int");
		$$->setStructure_type($1->getStructure_type());
        genCode("\t\tPOP AX");
        comment_out($3->getName()+ " loaded"); 
        if ($1->getStructure_type()=="array" && isGlobal()==false)
            genCode("\t\tPOP BX");
		genCode("\t\tMOV "+$1->getIcg_name()+", AX");
		genCode("\t\tPUSH AX");


    }
    ;

logic_expression:   rel_expression
    {
        $$=new SymbolInfo($1->getName(),"logic_expression");
		$$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type($1->getData_type());
		$$->setStructure_type($1->getStructure_type());
        showRule("logic_expression: rel_expression"); 
    }
    |   rel_expression LOGICOP  {

        comment_out("For expression: "+ $1->getName()+ " , Short circuit code for jumping");
		genCode("\t\tPOP AX");
        comment_out($1->getName()+ " loaded");
		string check; 
        if($2->getName()=="&&"){
            check= "1"; 
        }
        else{
            check ="0"; 
        }
		genCode("\t\tCMP AX, "+check);
		string j_label = newLabel();
		genCode("\t\tJNE "+j_label);
		$1->set_label(j_label);

    } rel_expression
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$4->getName(),"logic_expression");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($4);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($4->getEndLine());
        $$->setData_type("int");
        $$->setStructure_type($1->getStructure_type());
        showRule("logic_expression: rel_expression LOGICOP rel_expression");
        if($1->getData_type().compare("void")==0 || $4->getData_type().compare("void")==0 ){
            error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
            errors++;
        }

        comment_out($$->getName());
		genCode("\t\tPOP AX");
        comment_out($4->getName()+" loaded"); 
		string boolVal = $2->getName() == "&&" ? "1" : "0";


		genCode("\t\tCMP AX, "+boolVal);
		genCode("\t\tJNE "+$1->get_label());

        string check; 
        if($2->getName()=="&&"){
            check= "1"; 
        }
        else{
            check ="0"; 
        }
		genCode("\t\t\tPUSH "+check);
		string logic_label = newLabel();
		genCode("\t\t\tJMP "+logic_label);
		genCode("\t\t"+$1->get_label()+":");
        if($2->getName()=="&&"){
            check= "0"; 
        }
        else{
            check ="1"; 
        }
		genCode("\t\t\tPUSH " +check);
		genCode("\t\t"+logic_label+":\n");

    }
    ;

rel_expression:     simple_expression
    {
        $$=new SymbolInfo($1->getName(),"rel_expression");
		$$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type($1->getData_type());
        $$->setStructure_type($1->getStructure_type());
        showRule("rel_expression: simple_expression");
    }
    |   simple_expression RELOP simple_expression
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName(),"rel_expression");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
        $$->setData_type("int");
        $$->setStructure_type($1->getStructure_type());
        showRule("rel_expression:   simple_expression RELOP simple_expression");
        if($1->getData_type().compare("void")==0 || $3->getData_type().compare("void")==0 ){
            error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
            errors++;
        }

        string true_label = newLabel();
		string end_label = newLabel();

        string relat_op; 
        
        if($2->getName() == "<") relat_op= "JL";
        if($2->getName() == "<=") relat_op= "JLE";
        if($2->getName() == ">") relat_op= "JG";
        if($2->getName() == ">=") relat_op= "JGE";
        if($2->getName() == "==") relat_op= "JE";
        if($2->getName() == "!=") relat_op= "JNE";

        comment_out($$->getName());
        genCode("\t\tPOP BX");
        comment_out($3->getName()+ " loaded"); 
		genCode("\t\tPOP AX");
        comment_out($1->getName()+ " loaded"); 
		genCode("\t\tCMP AX, BX");
		genCode("\t\t"+relat_op+" "+true_label);
		genCode("\t\t\tPUSH 0"); 
        genCode("\t\t\tJMP "+end_label); 
		genCode("\t\t"+true_label+":\n\t\t\tPUSH 1");
		genCode("\t\t"+end_label+":\n");

    }
    ;

simple_expression:  term
    {
        $$=new SymbolInfo($1->getName(),"simple_expression");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
		$$->setData_type($1->getData_type());
        showRule("simple_expression: term"); 
		$$->setStructure_type($1->getStructure_type());
    }
    |   simple_expression ADDOP term
    {

		$$=new SymbolInfo($1->getName()+" "+$2->getName()+ " "+ $3->getName(),"simple_expression");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
        if($1->getData_type().compare("float")==0 || $3->getData_type().compare("float")==0)
			$$->setData_type("float");
		else if($1->getData_type().compare("int")==0 || $3->getData_type().compare("int")==0)
			$$->setData_type("int");
		else if($1->getData_type().compare("void")==0 || $3->getData_type().compare("void")==0 ){
                error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
                errors++;
        }
        else{
            error_out<<"Invalid data type"<<endl; 

        }
        comment_out($$->getName()); 

        genCode("\t\tPOP BX");
        comment_out($3->getName()+ " loaded"); 

		genCode("\t\tPOP AX");
        comment_out($1->getName()+ " loaded"); 
        string addst; 
        if($2->getName()=="+"){
            addst = "ADD";
        }
        else{
            addst= "SUB"; 
        }
		genCode("\t\t"+addst+" AX, BX");
		genCode("\t\tPUSH AX");
        comment_out($1->getName()+ " stored"); 
        
        showRule("simple_expression: simple_expression ADDOP term"); 
    }
    ;



term:   unary_expression
    {
		$$=new SymbolInfo($1->getName(),"term");
		$$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type($1->getData_type());
		$$->setStructure_type($1->getStructure_type());
        showRule("term:   unary_expression"); 
    }
    |   term MULOP unary_expression
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName(),"term");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
        

        if($1->getData_type()=="void" || $3->getData_type()=="void"){
                error_out<<"Line# "<<lines<<": function can't be void in expression"<<endl;
                errors++;        
        }

        if($2->getName()=="%"|| $2->getName()=="/"){
            if($1->getData_type()!="int" || $3->getData_type()!="int"){
                error_out<<"Line# "<<lines<<": must mod an integer by another integer"<<endl;
                errors++;                
            }

            if($3->getName()=="0"){
                error_out<<"Line# "<<lines<<": Warning, Divide by zero."<<endl;
                errors++;
            }
            $$->setData_type("int");
        }
        else{
            if($1->getData_type()=="float" || $3->getData_type()=="float"){
                $$->setData_type("float");
            }
            else{
                $$->setData_type("int");
            }
        }

        comment_out($$->getName()); 
        genCode("\t\tPOP BX");
        comment_out($3->getName()+ " loaded"); 

		genCode("\t\tPOP AX");
        comment_out($1->getName()+ " loaded"); 

		genCode("\t\tXOR DX, DX");
        comment_out("DX Register cleared"); 

		string mulst;
        if($2->getName()=="*"){
            mulst = "IMUL"; 
        }
        else{
            mulst= "IDIV"; 
        }
		genCode("\t\t"+mulst+" BX");

        string mulres; 

        if($2->getName()=="%"){
            mulres = "DX";
        }
        else{
            mulres="AX"; 
        }

		genCode("\t\tPUSH "+mulres);

        showRule("term:   MULOP unary_expression"); 

    }
    ;
    // done


unary_expression:   ADDOP unary_expression
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName(),"unary_expression");
		$$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
		$$->setData_type($2->getData_type());
        showRule("unary_expression:   ADDOP unary_expression");
        if($1->getName() == "-"){
            comment_out($$->getName()); 
			genCode("\t\tPOP AX");
			genCode("\t\tNEG AX");
			genCode("\t\tPUSH AX\n");
		}
    }
    |   NOT unary_expression
    {
		$$=new SymbolInfo($1->getName()+" "+$2->getName(),"unary_expression");
		$$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
        $$->setData_type($2->getData_type());
        showRule("unary_expression: NOT unary_expression");

        string not_label1 = newLabel();
		string not_label2 = newLabel(); 
		comment_out($$->getName());
		genCode("\t\tPOP AX");
		genCode("\t\tCMP AX, 0");
		genCode("\t\tJE "+not_label1);
		genCode("\t\t\tPUSH 0");
		genCode("\t\t\tJMP "+not_label2);
		genCode("\t\t"+not_label1+":"); 
        genCode("\n\t\tPUSH 1\n");
		genCode("\t\t"+not_label2+":");

    }
    | factor
    {
        $$=new SymbolInfo($1->getName(),"unary_expression");
		$$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        $$->setData_type($1->getData_type());
		$$->setStructure_type($1->getStructure_type());
        showRule("unary_expression: factor"); 
    }
    ;


factor:     variable
    {
        $$=new SymbolInfo($1->getName(),"factor");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        showRule("factor:     variable");
		$$->setData_type($1->getData_type());
		$$->setStructure_type($1->getStructure_type());

        if ($1->getStructure_type()=="array" && isGlobal()==false)
            genCode("\t\tPOP BX");

        genCode("\t\tPUSH "+$1->getIcg_name());

        comment_out($1->getName()+ " stored"); 


    }
    
    |   ID LPAREN {
        curr_call= $1->getName(); 

    } argument_list RPAREN
    {
        SymbolInfo* lookedUp=symbolTable->lookUp($1->getName());
        showRule("factor:   ID LPAREN argument_list RPAREN"); 

        $$->setData_type(lookedUp->getData_type());
        int size; 

		if(lookedUp==NULL){


            error_out<<"Line# "<<lines<<": Undeclared function '"<<$1->getName()<<"'"<<endl;
            errors++; 
			$$->setData_type("undefined");
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

               
            if($4->getName() != "("){
                $$=new SymbolInfo($1->getName()+$2->getName()+$4->getName()+$5->getName(),"factor");
                $$->addChild($1);
                $$->addChild($2);
                $$->addChild($4);  
                $$->addChild($5);
                $$->setStartLine($1->getStartLine()); 
                $$->setEndLine($5->getEndLine());
		    }
            else{
                $$=new SymbolInfo($1->getName()+$2->getName()+$5->getName(),"factor");
                $$->addChild($1);
                $$->addChild($2);
                $$->addChild($5);
                $$->setStartLine($1->getStartLine()); 
                $$->setEndLine($5->getEndLine());
            }

        
            $$->setData_type(lookedUp->getData_type());

            parameter_list.clear();

	    }

        comment_out("For return value"); 
        genCode("\t\tPUSH 0"); 
        
        comment_out("Calling function "+ $1->getName()); 
		genCode("\t\tCALL "+$1->getName());
		genCode("\t\tPOP AX");
        comment_out("Return value loaded"); 

        comment_out("Now removing function parameters from the stack"); 
		genCode("\t\tADD SP,"+to_string(size*2));
		if($1->getData_type() != "void"){
            comment_out("Return value stored "); 
			genCode("\t\tPUSH AX");
		}else{
            comment_out("For void function , default return value set to 0 "); 
			genCode("\t\tPUSH 0");
		}

    }

    |   LPAREN expression RPAREN
    {
        showRule("factor:   LPAREN expression RPAREN");
		$$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName(),"factor");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());

		$$->setData_type($2->getData_type());
    }
    |   CONST_INT
    {
        $$=new SymbolInfo($1->getName(),"factor");
		$$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());

        $$->setData_type("int");
        showRule("factor:   CONST_INT"); 
		$$->setStructure_type("val");

        comment_out("Store "+ $1->getName()); 
        genCode("\t\tPUSH " + $1->getName());


    }
    |   CONST_FLOAT
    {
        $$=new SymbolInfo($1->getName(),"factor");
		$$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());

        $$->setData_type("float");
        showRule("factor:   CONST_FLOAT"); 
		$$->setStructure_type("val");
        comment_out("Store "+ $1->getName()); 
        genCode("\t\tPUSH " + $1->getName());

    }
    |   variable INCOP
    {
        showRule("factor:   variable INCOP"); 
		$$=new SymbolInfo($1->getName()+" "+$2->getName(),"factor");
		$$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
        if ($1->getStructure_type()=="array" && isGlobal()==false)
            genCode("\t\tPOP BX");
        comment_out("Store "+ $1->getName()); 
        genCode("\t\tPUSH " + $1->getIcg_name());
        comment_out("Incremnt of "+ $1->getName()); 
        genCode("\t\tINC " + $1->getIcg_name());

    }
    |   variable DECOP
    {
        showRule("factor:   variable DECOP"); 
		$$=new SymbolInfo($1->getName()+" "+$2->getName(),"factor");
        $$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
        comment_out("Store "+ $1->getName()); 
        genCode("\t\tPUSH " + $1->getIcg_name());
        comment_out("Decrement of "+ $1->getName()); 
        genCode("\t\tDEC "+ $1->getIcg_name());

    }
    ;

argument_list:  arguments
    {
        $$=new SymbolInfo($1->getName(),"argument_list");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());

        $$->setData_type($1->getData_type());
        $$->setStructure_type($1->getStructure_type());

        // parse_out<<debugGetType<<endl; 

        showRule("argument_list:  arguments"); 
	}
	| {
		$$=new SymbolInfo(" ","argument_list");
        showRule("argument_list:  arguments"); 
    }
    ;

arguments:  arguments COMMA logic_expression
    {
        $$=new SymbolInfo($1->getName()+$2->getName()+$3->getName(),"arguments");
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());

        showRule("arguments:  arguments COMMA logic_expression");

 
		parameter_list.push_back(*$3);
    }
    |   logic_expression
    {
        $$=new SymbolInfo($1->getName(),"arguments");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());

		$$->setData_type($1->getData_type());
		$$->setStructure_type($1->getStructure_type());
        showRule("arguments:    logic_expression");
        parameter_list.push_back(*$1);
    }
    ;
     
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