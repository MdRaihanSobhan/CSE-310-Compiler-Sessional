#include "SymbolInfo.h"
#include <iostream>
#include<stdio.h>
#include<cstring>
#define ll long long int
#include <sstream>
#include <fstream>
#pragma once
using namespace std;
SymbolInfo::SymbolInfo()
{
    this->nextSymbol= NULL;
}

SymbolInfo::SymbolInfo(string name, string type)
{
    this->name= name;
    this->type= type;
    this-> nextSymbol= NULL;
}

void SymbolInfo::setName(string name)
{
    this->name = name;
}
void SymbolInfo::setType(string type)
{
    this->type = type;
}

void SymbolInfo::setNext(SymbolInfo *next)
{
    this->nextSymbol= next;
}


string SymbolInfo::getName()
{
    return this->name;
}
string SymbolInfo::getType()
{
    return  this->type;
}

SymbolInfo* SymbolInfo::getNext()
{
    return this->nextSymbol;
}


SymbolInfo::~SymbolInfo()
{
    //dtor
}
