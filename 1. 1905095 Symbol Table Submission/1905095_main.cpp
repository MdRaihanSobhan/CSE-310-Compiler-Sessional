//
//  main.cpp
//  1905095
//
//  Created by Md. Raihan Sobhan on 29/11/22.
//
#include"1905095_SymbolInfo.cpp"
#include"1905095_ScopeTable.cpp"
#include"1905095_SymbolTable.cpp"

#include<stdio.h>
#include<cstring>
#define ll long long int
#include <sstream>
#include <fstream>
#define ll long long int

using namespace std;

int main(int argc, const char * argv[])
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ll cnt=1;
    ll n;
    cin>>n;
    string inputSymbol;
    SymbolTable symbolTable(n);


    string s1, s2;

    char str[100];

    cin.getline(str, 100);

    char *ptr;
    ptr = strtok(str, " ");


    while (cin.getline(str, 100))
    {
        ptr = strtok(str, " ");
        // cout<<ptr<<endl;

        while (ptr != NULL)
        {
            inputSymbol= ptr;
            inputSymbol.erase(remove(inputSymbol.begin(), inputSymbol.end(), '\r'),
                              inputSymbol.end());
            if(inputSymbol=="Q")
            {
                // remove all scopetables
                cout<<"Cmd "<<cnt++<<": ";
                cout<<inputSymbol<<endl;
                while (symbolTable. getCurrent_scope()->getParentScope()!=NULL)
                {
                    symbolTable.exit_scope();
                }
                ScopeTable* temp_scope =symbolTable.getCurrent_scope();

                printf("\tScopeTable# %lld removed",temp_scope->getId());
                delete temp_scope;

                // symbolTable.getCurrent_scope()

                break;
            }
            else if(inputSymbol=="I")
            {

                cout<<"Cmd "<<cnt++<<": ";
                cout<<inputSymbol;

                ptr = strtok (NULL, " ");
                if(ptr!=NULL)
                {
                    s1= ptr;
                    s1.erase(remove(s1.begin(), s1.end(), '\r'),
                             s1.end());
                    cout<<" "<<s1;
                }
                else
                {
                    cout<<"\n\tNumber of parameters mismatch for the command I"<<endl;
                    break;
                }

                ptr = strtok (NULL, " ");
                if(ptr!=NULL)
                {
                    s2= ptr;
                    s2.erase(remove(s2.begin(), s2.end(), '\r'),
                             s2.end());
                    cout<<" "<<s2;
                }
                else
                {
                    cout<<"\n\tNumber of parameters mismatch for the command I"<<endl;
                    break;
                }

                ptr = strtok (NULL, " ");
                ll flag=0;
                while (ptr!=NULL)
                {
                    flag=1;
                    s2= ptr;
                    cout<<" "<<s2;
                    ptr = strtok (NULL, " ");
                }
                if(flag==1)
                {
                    cout<<"\n\tNumber of parameters mismatch for the command I"<<endl;
                    break;
                }
                //cout<<"calling insert \t"<<endl;
                cout<<"\n\t";

                symbolTable.Insert(SymbolInfo(s1,s2));
                //cout<<"insertion done"<<endl;
            }
            else if(inputSymbol=="L")
            {
                cout<<"Cmd "<<cnt++<<": ";
                cout<<inputSymbol;

                ptr = strtok (NULL, " ");
                if(ptr!=NULL)
                {
                    s1= ptr;
                    cout<<" "<<s1;
                }
                else
                {
                    cout<<"\tNumber of parameters mismatch for the command L"<<endl;
                    break;
                }

                ptr = strtok (NULL, " ");
                ll flag=0;
                while (ptr!=NULL)
                {
                    flag=1;
                    s2= ptr;
                    cout<<" "<<s2;
                    ptr = strtok (NULL, " ");
                }
                if(flag==1)
                {
                    cout<<"\n\tNumber of parameters mismatch for the command L"<<endl;
                    break;
                }

                s1.erase(remove(s1.begin(), s1.end(), '\r'),
                         s1.end());
                cout<<"\n\t";
                symbolTable.lookUp(s1);
                //cout<<"look up done"<<endl;
            }
            else if(inputSymbol=="D")
            {

                cout<<"Cmd "<<cnt++<<": ";
                cout<<inputSymbol;

                ptr = strtok (NULL, " ");
                if(ptr!=NULL)
                {
                    s1= ptr;
                    cout<<" "<<s1;
                }
                else
                {
                    cout<<"\n\tNumber of parameters mismatch for the command D"<<endl;
                    break;
                }

                ptr = strtok (NULL, " ");
                ll flag=0;
                while (ptr!=NULL)
                {
                    flag=1;
                    s2= ptr;
                    cout<<" "<<s2;
                    ptr = strtok (NULL, " ");
                }
                if(flag==1)
                {
                    cout<<"\n\tNumber of parameters mismatch for the command D"<<endl;
                    break;
                }

                s1.erase(remove(s1.begin(), s1.end(), '\r'),
                         s1.end());
                cout<<"\n\t";
                symbolTable.Remove(s1);
            }
            else if(inputSymbol=="P")
            {
                cout<<"Cmd "<<cnt++<<": ";
                cout<<inputSymbol;

                ptr = strtok (NULL, " ");
                if(ptr!=NULL)
                {
                    s1= ptr;
                    // s1= s1[0];
                    cout<<" "<<s1;
                }
                else
                {
                    cout<<"\n\tNumber of parameters mismatch for the  command P"<<endl;
                    break;
                }

                ptr = strtok (NULL, " ");
                ll flag=0;
                while (ptr!=NULL)
                {
                    flag=1;
                    s2= ptr;
                    cout<<" "<<s2;
                    ptr = strtok (NULL, " ");
                }
                if(flag==1)
                {
                    cout<<"\n\tNumber of parameters mismatch for the command P"<<endl;
                    break;
                }
                s1.erase(remove(s1.begin(), s1.end(), '\r'),
                         s1.end());
                cout<<endl;

                if(s1=="C")
                {
                    symbolTable.print_current_scope();
                }
                else if(s1=="A")
                {
                    symbolTable.print_all_scopes();
                }
            }
            else if(inputSymbol=="S")
            {
                cout<<"Cmd "<<cnt++<<": ";
                cout<<inputSymbol;

                ptr = strtok (NULL, " ");
                ll flag=0;
                while (ptr!=NULL)
                {
                    flag=1;
                    s2= ptr;
                    cout<<" "<<s2;
                    ptr = strtok (NULL, " ");
                }
                if(flag==1)
                {
                    cout<<"\n\tNumber of parameters mismatch for the command S"<<endl;
                    break;
                }
                cout<<endl;
                //cout<<"\t";

                symbolTable.enter_scope();
            }
            else if(inputSymbol=="E")
            {
                cout<<"Cmd "<<cnt++<<": ";
                cout<<inputSymbol;

                ptr = strtok (NULL, " ");
                ll flag=0;
                while (ptr!=NULL)
                {
                    flag=1;
                    s2= ptr;
                    cout<<" "<<s2;
                    ptr = strtok (NULL, " ");
                }
                if(flag==1)
                {
                    cout<<"\n\tNumber of parameters mismatch for the command E"<<endl;
                    break;
                }
                cout<<endl;
                //cout<<"\t";
                symbolTable.exit_scope();
            }
            else
            {
                cout<<"\tInvalid Operation"<<endl;
            }


            if(ptr!=NULL)
                ptr = strtok (NULL, " ");

        }
        // cin>>inputSymbol;

    }

    return 0;
}
