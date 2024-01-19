#ifndef SCOPETABLE_H
#define SCOPETABLE_H


#include"SymbolInfo.cpp"
#define ll long long int
#include <iostream>
#include<stdio.h>
#include<cstring>
#define ll long long int
#include <sstream>
#include <fstream>

using namespace std;


class ScopeTable
{
    ll size;
    ll id;

    SymbolInfo** hashTable;

    bool lookUpForInsertion(string name)
    {
        ll hash = hash_function(name);
        SymbolInfo* lookedUp = hashTable[hash];
        while (lookedUp)
        {
            if(lookedUp->getName()==name)
            {
                return true;
            }
            lookedUp= lookedUp->getNext();
        }
        return false;
    }


public:

    ScopeTable* parent_scope;


    ScopeTable(ll n, ll id, ScopeTable* parent_scope);

    ScopeTable(ll n);
    void setId(ll id);

    ll getId();

    void setPartentScope(ScopeTable* parent);

    ScopeTable* getParentScope();

    ll SDBMHash(string str);

    ll hash_function(string str);


    bool Insert(SymbolInfo symbol);


    SymbolInfo* lookUp(string name);
    bool Delete(string name);

    void Print();
    ~ScopeTable();
};



#endif // SCOPETABLE_H
