#ifndef CAMPO
#define CAMPO value

#include <vector>

#include <iostream>
#include <string>

using namespace std;

class Campo
{
private:
    // CHAR = 0;
    // INT = 1;
    // FLOAT = 2;

    string nombre;
	int tipo;
    int longitud;
    int decimal;
    bool llave;

public:
	Campo();
	~Campo();
    bool crearCampo(string,int,int,int,bool); //crea un campo

    //obtiene o modifica cada atributo de un campo
    bool setNombre(string);
    string getNombre();
    bool setTipo(int);
	int getTipo();
    bool setLongitud(int);
    int getLongitud();
    bool setDecimal(int);
    int getDecimal();
    bool setLlave(bool);
    bool getLlave();
};

#endif

