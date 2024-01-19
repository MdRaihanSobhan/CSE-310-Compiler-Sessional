#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#define ll long long int

#include"SymbolInfo.cpp"
#include"ScopeTable.cpp"

#include <iostream>
#include<stdio.h>
#include<cstring>
#define ll long long int
#include <sstream>
#include <fstream>
using namespace std;

class SymbolTable
{
    ll size;
    ScopeTable* current_scope;
    static ll id;

public:
    SymbolTable(ll size);
    ScopeTable* getCurrent_scope();
    void enter_scope();

    void exit_scope();

    bool Insert(SymbolInfo symbol);
    bool Remove(string name);
    SymbolInfo* lookUp(string name);
    void print_current_scope();

    void print_all_scopes();
    ~SymbolTable();
};

ll SymbolTable::id = 1;



#endif // SYMBOLTABLE_H
