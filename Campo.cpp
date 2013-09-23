#include "Campo.h"

Campo::Campo(){

}

bool Campo::crearCampo(string nombre, int tipo, int longitud, int decimal, bool llave){
    this->nombre=nombre;
    this->tipo=tipo;
    this->longitud=longitud;
    this->decimal=decimal;
    this->llave=llave;
    return true;
}


string Campo::getNombre(){
	return this->nombre;
}

int Campo::getTipo(){
	return this->tipo;
}

int Campo::getLongitud(){
    return this->longitud;
}

int Campo::getDecimal(){
    return this->decimal;
}

bool Campo::getLlave(){
    return this->llave;
}

bool Campo::setNombre(string nombre){
    this->nombre=nombre;
    return true;
}

bool Campo::setTipo(int tipo){
    this->tipo=tipo;
    return true;
}

bool Campo::setLongitud(int longitud){
    this->longitud=longitud;
    return true;
}

bool Campo::setDecimal(int decimal){
    this->decimal=decimal;
    return true;
}

bool Campo::setLlave(bool llave){
    this->llave=llave;
    return true;
}
