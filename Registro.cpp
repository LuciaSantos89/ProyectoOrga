#include "Registro.h"

Registro::Registro()
{
}

void Registro::crearRegistro(vector<string> registro,vector<Campo*> campos){
    this->registro=registro;
    this->campos=campos;
}

string Registro::convertirAString(){
    stringstream tmp;
    for (unsigned int i = 0; i < campos.size(); i++) {
        int tam=campos.at(i)->getLongitud();
        tmp<<setw(tam)<<setfill(' ')<<registro.at(i);
    }
    return tmp.str();
}

string Registro::campoLLave(){
    stringstream tmp;
    for (unsigned int i = 0; i < campos.size(); i++) {
        if(campos.at(i)->getLlave()){
            tmp<<registro.at(i);
            return tmp.str();
        }
    }
    return "";
}


vector<Campo*> Registro::getCampos(){
    return campos;
}

vector<string> Registro::getRegistro(){
    return registro;
}
