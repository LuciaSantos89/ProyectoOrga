#ifndef TDARECORDFILE
#define TDARECORDFILE

#include "Campo.h"
#include "TDAFile.h"
#include "Registro.h"
#include "Index.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <map>

using namespace::std;

class TDARecordFile:public TDAFile
{
public:
    TDARecordFile();
	~TDARecordFile();

    void getAvaillist(int);

    //Secuencial
    /*bool addRecord(vector <Campo*>,vector<string>);
    string* searchRecord(string);
	bool deleteRecord(int);
    string* listRecord(vector <Campo*>);*/

    //Indices Simples
    bool addRecord(Registro*,Index*); //Recibe un apuntador al registro
    Registro* searchRecord(string, vector<Campo*>, Index*); //Recibe la llave y la lista de campos
    bool deleteRecord(string,Index*); //Recibe la llave
    vector<Registro*> listRecord(vector <Campo*>,Index*);
    void guardarIndices(Index*,string);
    map<string,int> abrirIndices(string);
    void guardarXML(vector <Campo*>, Index*,string);

    //Indices Arbol B


private:
    map <string,int> indices;
    stack<int> AvailList;
    vector<Registro*> registros;
};
#endif
