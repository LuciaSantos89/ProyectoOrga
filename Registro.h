#ifndef REGISTRO_H
#define REGISTRO_H

#include "Campo.h"

#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Registro
{
public:
    Registro();
    ~Registro();
    void crearRegistro(vector<string>,vector<Campo*>);
    string convertirAString();
    string campoLLave();
    vector<Campo*> getCampos();
    vector<string> getRegistro();

private:
    vector <string> registro;
    vector <Campo*> campos;
};

#endif // REGISTRO_H
