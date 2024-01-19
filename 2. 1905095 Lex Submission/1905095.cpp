//
//  main.cpp
//  1905095
//
//  Created by Md. Raihan Sobhan on 29/11/22.
//


#include <iostream>
#include<stdio.h>
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

public:
    SymbolInfo()
    {
        this->nextSymbol= NULL;
    }
    SymbolInfo(string name, string type)
    {
        this->name= name;
        this->type= type;
        this-> nextSymbol= NULL;
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


    ~SymbolInfo()
    {

    }

};


class ScopeTable
{
    ll size;
    ll id;

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
        this->parent_scope= NULL;
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


    bool Insert(SymbolInfo symbol){
        if(lookUpForInsertion(symbol.getName())){
            // printf("\t'%s' already exists in the current ScopeTable\n", symbol.getName().c_str());
            return false;
        }

        ll hash = hash_function(symbol.getName());
        SymbolInfo* toInsert = hashTable[hash];
        if(!toInsert){
            hashTable[hash] = new SymbolInfo(symbol.getName(),symbol.getType());
            // printf("Inserted in ScopeTable# %lld at position %lld, 1\n",id,hash+1);
        }
        else{
            ll position= 2;
            while (toInsert->getNext()) {
                position++;
                toInsert= toInsert->getNext();
            }
            SymbolInfo* newSymbol= new SymbolInfo(symbol.getName(), symbol.getType());
            toInsert->setNext(newSymbol);
            // printf("Inserted in ScopeTable# %lld at position %lld, %lld\n",id,hash+1, position);
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

    void Print(ofstream & out){
        out<<"\tScopeTable# "<<this->id<<endl;
        for(ll i=0; i<size; i++){

            SymbolInfo* toPrint = hashTable[i];
            if(hashTable[i]==NULL)
                    continue;

            out<<"\t"<<i+1<<"--> ";
            while (toPrint) {
                out<<"<"<<toPrint->getName()<<","<<toPrint->getType()<<"> "; 
                
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
    static ll id;

public:
    SymbolTable(ll size){
        this->size= size;

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
    bool Remove(string name){
        return this->current_scope->Delete(name);
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

    ~SymbolTable()
    {
        //delete current_scope;
    }
};

ll SymbolTable::id = 1;
