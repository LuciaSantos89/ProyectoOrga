#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <map>
#include <iostream>
using namespace::std;

class Index
{
public:
    Index();
    Index(map<string,int>);
    ~Index();
    void agregarIndice(string,int);
    void eliminarIndice(string);
    int getOffset(string);
    void cambiarIndice(string,string);
    bool verificarIndice(string);
    map <string,int> getIndices();

private:
    string pkey;
    int offset;
    map <string,int> indices;
};

#endif // INDEX_H
