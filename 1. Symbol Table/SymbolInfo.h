#ifndef SYMBOLINFO_H
#define SYMBOLINFO_H

#include <iostream>
#include<stdio.h>
#include<cstring>
#define ll long long int
#include <sstream>
#include <fstream>
using namespace std;

class SymbolInfo
{
    SymbolInfo* nextSymbol;
    string name;
    string type;

public:

    SymbolInfo();
    SymbolInfo(string name, string type);

    void setName(string name);
    void setType(string type);
    void setNext(SymbolInfo *next);

    string getName();
    string getType();
    SymbolInfo* getNext();

    ~SymbolInfo();
};


#endif // SYMBOLINFO_H

