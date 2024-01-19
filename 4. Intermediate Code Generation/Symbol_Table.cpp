//
//  main.cpp
//  1905095
//
//  Created by Md. Raihan Sobhan on 29/11/22.
//


#include <iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<cstring>
#define ll long long int
#include <sstream>
#include<fstream>

using namespace std;


class SymbolInfo
{
    SymbolInfo* nextSymbol;
    string name;
    string type;
    string data_type;
	string structure_type;

    string icg_name; 
    ll arr_size;
    ll arr_begin; 
    string label;

    ll startLine;
	ll endLine;
    bool isLeaf;
    vector<SymbolInfo> parameter_list; 


public:

    void copy_symbol(SymbolInfo temp){
        this->name = temp.getName(); 
        this->type= temp.getType(); 
        this->data_type= temp.getData_type(); 
        this->structure_type = temp.getStructure_type(); 
        this->icg_name= temp.getIcg_name(); 
        this->arr_size= temp.getArr_size(); 
        this->arr_begin= temp.getArr_begin(); 
        this->startLine= temp.getStartLine(); 
        this->endLine = temp.getEndLine(); 
        this->isLeaf = temp.getLeaf(); 
        this->parameter_list = temp.getParameterList(); 
        this->label= temp.get_label(); 

    }

	vector<SymbolInfo*> child_list;
    SymbolInfo()
    {
        this->nextSymbol= NULL;
        this->arr_size=0; 
    }
    SymbolInfo(string name, string type)
    {
        this->name= name;
        this->type= type;
        this-> nextSymbol= NULL;
        this->arr_size=0; 
    }

    SymbolInfo(string name, string type, vector<SymbolInfo> p_list){
        this->name= name;
        this->type= type;
        this-> nextSymbol= NULL;
        this->parameter_list = p_list; 
        this->arr_size=0; 

    }


    SymbolInfo(string name, string type, bool leaf, int start, int end)
    {
        this->name= name;
        this->type= type;
        this-> nextSymbol= NULL;
        this->isLeaf= leaf; 
        this->endLine= end;
        this->startLine=start; 
        this->arr_size=0; 
    }

    string get_label(){
        return this->label; 
    }
    void set_label(string str1){
        this->label=str1; 
    }

    bool is_arr(){
        this->arr_size != 0? true : false; 
    }
    void setArr_size(ll n){
        this->arr_size= n; 
    }
    ll getArr_size(){
        return this->arr_size; 
    }

    void setArr_begin(ll n){
        this->arr_begin= n; 
    }
    ll getArr_begin(){
        return this->arr_begin; 
    }

    void setIcg_name(string name){
        this->icg_name = name; 
    }
    string getIcg_name(){
        return this->icg_name; 
    }

    void setLeaf(bool leaf){
        this->isLeaf= leaf; 
    }

    bool getLeaf(){
        return this->isLeaf;
    }

    void setName(string name)
    {
        this->name = name;
    }
    void setType(string type)
    {
        this->type = type;
    }
    void setNext(SymbolInfo *next){
        this->nextSymbol= next;
    }

    void setData_type(string data_type){
        this->data_type = data_type; 
    }
    void setStructure_type(string structure_type){
        this->structure_type= structure_type;
    }

    void addParameter(SymbolInfo param){
        parameter_list.push_back(param);
    }

    void addChild(SymbolInfo* child){
        child_list.push_back(child); 
    }
    
    void setStartLine(ll startLine){
        this->startLine= startLine; 
    }
    void setEndLine(ll endLine){
        this->endLine = endLine;
    }


    string getName()
    {
        return this->name;
    }
    string getType()
    {
        return  this->type;
    }

    SymbolInfo* getNext(){
        return this->nextSymbol;
    }

    string getData_type(){
        return this->data_type;
    }
    string getStructure_type(){
        return this->structure_type;
    }
    
    vector<SymbolInfo*> getChild_List(){
        return this->child_list; 
    }
    vector<SymbolInfo> getParameterList(){
        return this->parameter_list; 
    }

    ll getStartLine(){
        return this->startLine; 
    }
    ll getEndLine(){
        return this->endLine; 
    }


    ~SymbolInfo()
    {

    }

};


class ScopeTable
{
    ll size;
    ll id;
    ll no_of_vars; 
    SymbolInfo** hashTable;

    bool lookUpForInsertion(string name){
        ll hash = hash_function(name);
        SymbolInfo* lookedUp = hashTable[hash];
        while (lookedUp) {
            if(lookedUp->getName()==name){
                return true;
            }
            lookedUp= lookedUp->getNext();
        }
        return false;
    }


public:

    ScopeTable* parent_scope;


    ScopeTable(ll n, ll id, ScopeTable* parent_scope)
    {
        this->hashTable= new SymbolInfo* [n];
        for(ll i=0; i<n; i++){
            hashTable[i]= NULL;
        }
        this->no_of_vars=0; 
        this->size= n;
        this->id= id;
        this->parent_scope= parent_scope;
    }

    ScopeTable(ll n)
    {
        this->hashTable= new SymbolInfo* [n];
        for(ll i=0; i<n; i++){
            hashTable[i]= NULL;
        }
        this->size= n;
        this->no_of_vars=0; 
        this->parent_scope= NULL;
    }


    void addvar(ll n=1){
        this->no_of_vars = this->no_of_vars+ n;
    }
    ll get_no_of_vars(){
        return this->no_of_vars; 
    }

    void setId(ll id){
        this->id= id;
    }

    ll getId(){
        return id;
    }

    void setPartentScope(ScopeTable* parent){
        this->parent_scope= parent;
    }

    ScopeTable* getParentScope(){
        return this->parent_scope;
    }

    ll SDBMHash(string str) {
        ll hash = 0;
        ll i = 0;
        ll len = str.length();

        for (i = 0; i < len; i++)
        {
            hash = (str[i]) + (hash << 6) + (hash << 16) - hash;
            hash= hash% this->size;
        }

        return hash;
    }

    ll hash_function(string str){
        return (SDBMHash(str)%this->size) ;
    }

    bool InsertFunc(SymbolInfo symbol){
        if(lookUpForInsertion(symbol.getName())){
            // printf("\t'%s' already exists in the current ScopeTable\n", symbol.getName().c_str());
            return false;
        }

        ll hash = hash_function(symbol.getName());
        SymbolInfo* toInsert = hashTable[hash];
        if(!toInsert){
            hashTable[hash] = new SymbolInfo(symbol.getName(),symbol.getType(),symbol.getParameterList());
            hashTable[hash]->copy_symbol(symbol); 
            // printf("  Inserted in ScopeTable# %lld at position %lld, 1\n",id,hash+1);
        }
        else{
            ll position= 2;
            while (toInsert->getNext()) {
                position++;
                toInsert= toInsert->getNext();
            }
            SymbolInfo* newSymbol= new SymbolInfo(symbol.getName(), symbol.getType(), symbol.getParameterList());
            newSymbol->copy_symbol(symbol);
            toInsert->setNext(newSymbol);
            // printf(" Inserted in ScopeTable# %lld at position %lld, %lld\n",id,hash+1, position);
        }
        return true;
    }


    bool Insert(SymbolInfo symbol){
        if(lookUpForInsertion(symbol.getName())){
            // printf("\t'%s' already exists in the current ScopeTable\n", symbol.getName().c_str());
            return false;
        }

        ll hash = hash_function(symbol.getName());
        SymbolInfo* toInsert = hashTable[hash];
        if(!toInsert){
            hashTable[hash] = new SymbolInfo(symbol.getName(),symbol.getType());
            hashTable[hash]->copy_symbol(symbol); 

            // printf("  Inserted in ScopeTable# %lld at position %lld, 1\n",id,hash+1);
        }
        else{
            ll position= 2;
            while (toInsert->getNext()) {
                position++;
                toInsert= toInsert->getNext();
            }
            SymbolInfo* newSymbol= new SymbolInfo(symbol.getName(), symbol.getType());
            newSymbol->copy_symbol(symbol);
            toInsert->setNext(newSymbol);
            // printf(" Inserted in ScopeTable# %lld at position %lld, %lld\n",id,hash+1, position);
        }
        return true;

    }
    // index = hash_table+hash;


    SymbolInfo* lookUp(string name){
        ll hash = hash_function(name);
        SymbolInfo* lookedUp = hashTable[hash];
        ll position = 1;
        while (lookedUp) {
            if(lookedUp->getName()==name){
                // 'i' found in ScopeTable# 1 at
                //position 1, 1
                // printf("'%s' found in ScopeTable# %lld at position %lld, %lld\n", name.c_str(), this->id, hash+1, position );
                return lookedUp;
            }
            position++;
            lookedUp= lookedUp->getNext();
        }
        //'j' not found in any of the ScopeTables
       // printf("'%s' not found in any of the ScopeTables\n", name.c_str());
        return NULL;
    }

    bool Delete(string name){
        ll hash = hash_function(name);
        SymbolInfo* toDelete = hashTable[hash];
        SymbolInfo* toReplace = NULL;

        ll position = 1;
        while (toDelete) {
            if(toDelete->getName() == name){
                // printf("Deleted '%s' from ScopeTable# %lld at position %lld, %lld\n", name.c_str(), this->id, hash+1, position);

                if(!toReplace){
                    hashTable[hash]= toDelete->getNext();
                }
                else{
                    toReplace->setNext(toDelete->getNext());
                }
                delete toDelete;
                return true;

            }
            position++;
            toReplace = toDelete;
            toDelete = toDelete->getNext();
        }

        printf("Not found in the current ScopeTable\n");
        return false;
    }
    string toCapString(string st){
        string ch=""; 
        for(int i=0; i<strlen(st.c_str()); i++){
            ch+=toupper(st[i]); 
        }
        return ch; 
    }


    void Print(ofstream & out){
        out<<"\tScopeTable# "<<this->id<<endl;
        for(ll i=0; i<size; i++){

            SymbolInfo* toPrint = hashTable[i];
            if(hashTable[i]==NULL)
                    continue;

            out<<"\t"<<i+1<<"--> ";
            while (toPrint) {
                out<<"<"<<toPrint->getName()<<","<<toPrint->getType()<<", "<<toPrint->getIcg_name()<<" > "; 
                
                toPrint = toPrint->getNext();
            }
            out<<endl; 
        }
    }

    ~ScopeTable()
    {
        for(ll i=0; i<size; i++){
            delete (hashTable[i]);
        }
        delete [] hashTable;
    }

};


class SymbolTable{
    ll size;
    ScopeTable *current_scope;
    ll id;

public:
    SymbolTable(){}
    
    SymbolTable(ll size){
        this->size= size;
        id++;
        current_scope =
        new ScopeTable(size);
        current_scope->setId(id);
        current_scope->setPartentScope(NULL);
        // printf("\tScopeTable# %lld created\n",id);

    }
    ScopeTable* getCurrent_scope(){
        return this->current_scope;
    }

    void enter_scope(){
        ScopeTable* newScope = new ScopeTable(size);
        newScope->setPartentScope(current_scope);
        id++;
        newScope->setId(id);
        //this->current_scope->setId(newScope->getId());
        this->current_scope= newScope;
        // printf("\tScopeTable# %lld created\n",newScope->getId());
    }

    void exit_scope(){
        if(current_scope==NULL){
            return;
        }
        if(current_scope->getParentScope()==NULL){
            // printf("\tScopeTable# 1 cannot be removed\n");
            return;
        }
        ScopeTable* temp_scope = current_scope;
        this->current_scope= current_scope->parent_scope;
        // printf("\tScopeTable# %lld removed\n",temp_scope->getId());
        delete temp_scope;

    }

    bool Insert(SymbolInfo symbol){
        return this->current_scope->Insert(symbol);
    }
    
    bool InsertFunc(SymbolInfo symbol){
        return this->current_scope->InsertFunc(symbol); 
    }

    bool Remove(string name){
        return this->current_scope->Delete(name);
    }

    SymbolInfo* lookUpCurrentScope(string name){
        ScopeTable* temp_scope= this->current_scope;
        SymbolInfo* return_scope= temp_scope->lookUp(name);
        return return_scope;
    }

    SymbolInfo* lookUp(string name){
        ScopeTable* temp_scope= this->current_scope;

        while (temp_scope) {
            SymbolInfo* return_scope= temp_scope->lookUp(name);
            if(return_scope!=NULL){
                return return_scope;
            }

            temp_scope = temp_scope->getParentScope();
        }
        // printf("'%s' not found in any of the ScopeTables\n", name.c_str());
        return NULL;
    }

    void print_current_scope(ofstream &out){
        this->current_scope->Print(out);
    }

    void print_all_scopes(ofstream &out){
        ScopeTable* temp_scope = this->current_scope;
        while (temp_scope) {
            temp_scope->Print(out);
            temp_scope= temp_scope->getParentScope();
        }
    }

    void addvar(ll n=1){
        this->current_scope->addvar(n); 
    }
    ll get_no_of_vars(){
        return this->current_scope->get_no_of_vars(); 
    }

    ~SymbolTable()
    {
        //delete current_scope;
    }
};

