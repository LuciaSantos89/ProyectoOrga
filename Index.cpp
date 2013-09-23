#include "Index.h"

Index::Index()
{
    indices.clear();
}

Index::Index(map<string, int> in)
{
    indices.clear();
    indices=in;
}

Index::~Index()
{
}

void Index::agregarIndice(string llave, int offset){
    this->indices[llave]=offset;
}
int Index::getOffset(string llave){
    this->offset=-1;
    if(indices.count(llave)>0)
        this->offset=indices[llave];
    return this->offset;
}

void Index::eliminarIndice(string llave){
    indices.erase(llave);
}

void Index::cambiarIndice(string llaveVieja,string llaveNueva){
    this->getOffset(llaveVieja);
    this->indices.erase(llaveVieja);
    this->indices[llaveNueva]=this->offset;
}

bool Index::verificarIndice(string llave){
    if(this->getOffset(llave)==-1)
        return false;
    return true;
}

map <string,int> Index::getIndices(){
    return this->indices;
}
