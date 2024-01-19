%{
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


%}

%union  {
    SymbolInfo* symbol; 
}

%token <symbol> ADDOP MULOP INCOP RELOP ID CONST_INT CONST_FLOAT IF ELSE FOR WHILE DO BREAK CHAR FLOAT DOUBLE VOID RETURN CONTINUE PRINTLN ASSIGNOP LOGICOP NOT LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON DECOP INT SWITCH CASE DEFAULT BITOP CONST_CHAR SINGLE_LINE_STRING MULTI_LINE_STRING

%type <symbol> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start :     program
	{
		$$=new SymbolInfo($1->getName(),"start");
        debugString+=$1->getName(); 
		showRule("start : program");
		log_out<<"Total lines: "<<lines<<endl;
		log_out<<"Total errors: "<<errors<<endl;
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine()); 
        showParseTree($$,0);
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
			}
			temp->setData_type($1->getName());
			temp->setStructure_type("func");
            temp->setType($1->getType()); 
			parameter_list.clear();
			symbolTable->Insert(*temp);
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
				symbolTable->Insert(*temp);
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
	running_function=$2->getName();
    debugString+=$1->getName(); 
    debugGetType+=$1->getType(); 
	if(symbolTable->lookUp(running_function) == NULL){
		SymbolInfo* temp = new SymbolInfo(running_function, "ID");
		for(auto i : parameter_list){
			temp->addParameter(i);
		}
		temp->setStructure_type("func");
		temp->setData_type($1->getName());
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

    showRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
    string symName = $1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$7->getName();
    debugString+=$1->getName(); 
    $$ = new SymbolInfo(symName, "func");	
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
        running_function=$2->getName();
        if(symbolTable->lookUp(running_function) == NULL){
            SymbolInfo* temp = new SymbolInfo(running_function, $1->getType());
            
            temp->setStructure_type("func");
            temp->setData_type($1->getName());
            symbolTable->Insert(*temp);
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
        temp->setStructure_type("var");
        temp->setStructure_type($1->getName());
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
        parameter_list.push_back(*temp);
    }
    ;

compound_statement:     LCURL { 
        symbolTable->enter_scope(); 
        if(parameter_list.size() != 0){
            for(auto i : parameter_list){
                symbolTable->Insert(i);
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
        $$=new SymbolInfo($1->getName(),"type_specifier");
        $$->addChild($1);
        debugString+=$1->getName(); 
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
		showRule("type_specifier	: INT");
        curr_type="int"; 
	}
 	|   FLOAT	    
    {
        $$=new SymbolInfo($1->getName(),"type_specifier");
        $$->addChild($1); 
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
    	showRule("type_specifier	: FLOAT");
        curr_type= "float"; 
				
	}
 	|   VOID
    {
        $$=new SymbolInfo($1->getName(),"type_specifier");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
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

        if(curr_type!="void"){
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
        if(curr_type != "void"){
            symbolTable->Insert(*temp);
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
        if(curr_type != "void"){
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
        if(curr_type != "void"){
            symbolTable->Insert(*temp);
        }
							
	}
 	;
    
statements:     statement
    {
        $$=new SymbolInfo($1->getName(),"statements");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        showRule("statements:     statement"); 
    }
    |   statements statement
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName(),"statements");
        $$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
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
    }
    |   expression_statement
    {
        $$=new SymbolInfo($1->getName(),"statement");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        showRule("statement:    expression_statement"); 
    }
    |   compound_statement
    {
        $$=new SymbolInfo($1->getName(),"statement");
        $$->addChild($1);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($1->getEndLine());
        showRule("statement:    compound_statement"); 
    }
    |   FOR LPAREN expression statement expression statement expression RPAREN statement
    {

		$$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+" "+$6->getName()+" "+$7->getName(),"statement");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        $$->addChild($6);
        $$->addChild($7);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($7->getEndLine());
        showRule("statement:    FOR LPAREN expression_statement expression_statement expression RPAREN statement");
    }
    |   IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName(),"statement");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($5->getEndLine());
        showRule("statement:    IF LPAREN expression RPAREN statement");
    }
    |   IF LPAREN expression RPAREN statement ELSE statement
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName()+"\n"+$6->getName()+"\n"+$7->getName(),"statement");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        $$->addChild($6);
        $$->addChild($7);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($7->getEndLine());

        showRule("statement:    IF LPAREN expression RPAREN statement ELSE statement");
    }
    |   WHILE LPAREN expression RPAREN statement
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName()+" "+$4->getName()+" "+$5->getName(),"statement");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->addChild($4);
        $$->addChild($5);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($5->getEndLine());
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
    }
    ;

expression_statement:   SEMICOLON
    {
		$$ = new SymbolInfo($1->getName()+"\n","expression_statement");
		showRule("expression_statement:   SEMICOLON");
    }
    |   expression SEMICOLON
    {
		$$=new SymbolInfo($1->getName()+$2->getName()+"\n","expression_statement");
        $$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());
		showRule("expression_statement:   expression SEMICOLON");
    }
    ;

variable:   ID
    {
        showRule("variable: ID"); 
		SymbolInfo* lookedUp =symbolTable->lookUp($1->getName());
        bool errorflag = false;
        string errorMessage;
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
		
        
		$$->setData_type("int");
		$$->setStructure_type($1->getStructure_type());
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
    |   rel_expression LOGICOP rel_expression
    {
        $$=new SymbolInfo($1->getName()+" "+$2->getName()+" "+$3->getName(),"logic_expression");
		$$->addChild($1);
        $$->addChild($2);
        $$->addChild($3);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($3->getEndLine());
        $$->setData_type("int");
        $$->setStructure_type($1->getStructure_type());
        showRule("logic_expression: rel_expression LOGICOP rel_expression");
        if($1->getData_type().compare("void")==0 || $3->getData_type().compare("void")==0 ){
            error_out<<"Line# "<<lines<<": Void cannot be used in expression"<<endl;
            errors++;
        }
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
		$$=new SymbolInfo($1->getName()+$2->getName()+$3->getName(),"simple_expression");
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
        debugString+=$1->getName(); 
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

        if($2->getName()=="%"){
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
    }
    
    |   ID LPAREN {
        curr_call= $1->getName(); 

    } argument_list RPAREN
    {
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


		
        SymbolInfo* lookedUp=symbolTable->lookUp($1->getName());
        showRule("factor:   ID LPAREN argument_list RPAREN"); 

		if(lookedUp==NULL){
            error_out<<"Line# "<<lines<<": Undeclared function '"<<$1->getName()<<"'"<<endl;
            errors++; 
			$$->setData_type("undefined");
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
            $$->setData_type(lookedUp->getData_type());
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
    }
    |   variable INCOP
    {
        showRule("factor:   variable INCOP"); 
		$$=new SymbolInfo($1->getName()+" "+$2->getName(),"factor");
		$$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());

    }
    |   variable DECOP
    {
        showRule("factor:   variable DECOP"); 
		$$=new SymbolInfo($1->getName()+" "+$2->getName(),"factor");
        $$->addChild($1);
        $$->addChild($2);
        $$->setStartLine($1->getStartLine()); 
        $$->setEndLine($2->getEndLine());

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
        debugString+=$1->getName(); 

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
    yyin = fin; 

    yyparse();

    fclose(yyin);
    error_out.close();
    log_out.close();
    parse_out.close();

    return 0; 
}