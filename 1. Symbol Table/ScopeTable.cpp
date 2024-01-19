#include "ScopeTable.h"
#include"SymbolInfo.cpp"
#define ll long long int
#include <iostream>
#include<stdio.h>
#include<cstring>
#define ll long long int
#include <sstream>
#include <fstream>
#pragma once

using namespace std;

ScopeTable::ScopeTable(ll n, ll id, ScopeTable* parent_scope)
{
    this->hashTable= new SymbolInfo* [n];
    for(ll i=0; i<n; i++)
    {
        hashTable[i]= NULL;
    }
    this->size= n;
    this->id= id;
    this->parent_scope= parent_scope;
}

ScopeTable::ScopeTable(ll n)
{
    this->hashTable= new SymbolInfo* [n];
    for(ll i=0; i<n; i++)
    {
        hashTable[i]= NULL;
    }
    this->size= n;
    this->parent_scope= NULL;
}



void ScopeTable:: setId(ll id)
{
    this->id= id;
}

ll ScopeTable::getId()
{
    return id;
}

void ScopeTable::setPartentScope(ScopeTable* parent)
{
    this->parent_scope= parent;
}

ScopeTable* ScopeTable::getParentScope()
{
    return this->parent_scope;
}

ll ScopeTable::SDBMHash(string str)
{
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

ll ScopeTable::hash_function(string str)
{
    return (SDBMHash(str)%this->size) ;
}


bool ScopeTable::Insert(SymbolInfo symbol)
{
    if(lookUpForInsertion(symbol.getName()))
    {
        printf("'%s' already exists in the current ScopeTable\n", symbol.getName().c_str());
        return false;
    }

    ll hash = hash_function(symbol.getName());
    SymbolInfo* toInsert = hashTable[hash];
    if(!toInsert)
    {
        hashTable[hash] = new SymbolInfo(symbol.getName(),symbol.getType());
        printf("Inserted in ScopeTable# %lld at position %lld, 1\n",id,hash+1);
    }
    else
    {
        ll position= 2;
        while (toInsert->getNext())
        {
            position++;
            toInsert= toInsert->getNext();
        }
        SymbolInfo* newSymbol= new SymbolInfo(symbol.getName(), symbol.getType());
        toInsert->setNext(newSymbol);
        printf("Inserted in ScopeTable# %lld at position %lld, %lld\n",id,hash+1, position);
    }
    return true;

}
// index = hash_table+hash;


SymbolInfo* ScopeTable::lookUp(string name)
{
    ll hash = hash_function(name);
    SymbolInfo* lookedUp = hashTable[hash];
    ll position = 1;
    while (lookedUp)
    {
        if(lookedUp->getName()==name)
        {
            // 'i' found in ScopeTable# 1 at
            //position 1, 1
            printf("'%s' found in ScopeTable# %lld at position %lld, %lld\n", name.c_str(), this->id, hash+1, position );
            return lookedUp;
        }
        position++;
        lookedUp= lookedUp->getNext();
    }
    //'j' not found in any of the ScopeTables
    // printf("'%s' not found in any of the ScopeTables\n", name.c_str());
    return NULL;
}

bool ScopeTable::Delete(string name)
{
    ll hash = hash_function(name);
    SymbolInfo* toDelete = hashTable[hash];
    SymbolInfo* toReplace = NULL;

    ll position = 1;
    while (toDelete)
    {
        if(toDelete->getName() == name)
        {
            printf("Deleted '%s' from ScopeTable# %lld at position %lld, %lld\n", name.c_str(), this->id, hash+1, position);

            if(!toReplace)
            {
                hashTable[hash]= toDelete->getNext();
            }
            else
            {
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

void ScopeTable::Print()
{
    printf("\tScopeTable# %lld\n", this->id);
    for(ll i=0; i<size; i++)
    {
        printf("\t%lld--> ",i+1);
        SymbolInfo* toPrint = hashTable[i];
        while (toPrint)
        {
            printf("<%s,%s> ",toPrint->getName().c_str(), toPrint->getType().c_str());
            toPrint = toPrint->getNext();
        }
        printf("\n");
    }
}

ScopeTable::~ScopeTable()
{
    for(ll i=0; i<size; i++)
    {
        delete (hashTable[i]);
    }
    delete [] hashTable;
}
