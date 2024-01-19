#include "SymbolTable.h"
#include"SymbolInfo.cpp"
#include"ScopeTable.cpp"
#include <iostream>
#include<stdio.h>
#include<cstring>
#define ll long long int
#include <sstream>
#include <fstream>
using namespace std;

SymbolTable::SymbolTable(ll size)
{
    this->size= size;

    current_scope =
        new ScopeTable(size);
    current_scope->setId(id);
    current_scope->setPartentScope(NULL);
    printf("\tScopeTable# %lld created\n",id);

}
ScopeTable* SymbolTable::getCurrent_scope()
{
    return this->current_scope;
}

void SymbolTable::enter_scope()
{
    ScopeTable* newScope = new ScopeTable(size);
    newScope->setPartentScope(current_scope);
    id++;
    newScope->setId(id);
    //this->current_scope->setId(newScope->getId());
    this->current_scope= newScope;
    printf("\tScopeTable# %lld created\n",newScope->getId());
}

void SymbolTable::exit_scope()
{
    if(current_scope==NULL)
    {
        return;
    }
    if(current_scope->getParentScope()==NULL)
    {
        printf("\tScopeTable# 1 cannot be removed\n");
        return;
    }
    ScopeTable* temp_scope = current_scope;
    this->current_scope= current_scope->parent_scope;
    printf("\tScopeTable# %lld removed\n",temp_scope->getId());
    delete temp_scope;

}

bool SymbolTable::Insert(SymbolInfo symbol)
{
    return this->current_scope->Insert(symbol);
}
bool SymbolTable::Remove(string name)
{
    return this->current_scope->Delete(name);
}

SymbolInfo* SymbolTable::lookUp(string name)
{
    ScopeTable* temp_scope= this->current_scope;

    while (temp_scope)
    {
        SymbolInfo* return_scope= temp_scope->lookUp(name);
        if(return_scope!=NULL)
        {
            return return_scope;
        }

        temp_scope = temp_scope->getParentScope();
    }
    printf("'%s' not found in any of the ScopeTables\n", name.c_str());
    return NULL;
}

void SymbolTable::print_current_scope()
{
    this->current_scope->Print();
}

void SymbolTable::print_all_scopes()
{
    ScopeTable* temp_scope = this->current_scope;
    while (temp_scope)
    {
        temp_scope->Print();
        temp_scope= temp_scope->getParentScope();
    }
}

SymbolTable::~SymbolTable()
{
    //delete current_scope;
}
