#include "Header.h"

Header::Header()
{
    this->campos.clear();
    this->header="";
}


void Header::crearHeader(vector<Campo*> campos){
    this->campos=campos;
    int tam= this->campos.size();
    stringstream tmp;
    tmp<<tam<<",";
    for (int i = 0; i < tam; i++) {
        //nombre
        tmp<< this->campos.at(i)->getNombre()<<",";
        //tipo
        tmp<<this->campos.at(i)->getTipo()<<",";
        //longitud
        tmp<<this->campos.at(i)->getLongitud()<<",";
        //decimal
        tmp<<this->campos.at(i)->getDecimal()<<",";
        //llave
        tmp<<this->campos.at(i)->getLlave()<<",";
    }
    tmp<<"#";
    this->header=tmp.str();
}


void Header::guardarHeader(TDAFile* archivo){
    if(archivo->isOpen()){
        if(this->header.size()==0)
            return;
        archivo->seek(ios_base::beg);
        archivo->write(this->header.c_str(), this->header.size());
        archivo->flush();
    }
}

void Header::recuperarHeader(TDAFile *archivo){
    char buf[1];
    if(archivo->isOpen()){
        archivo->seek(0,ios_base::beg);
        while(*buf!='#' && !archivo->eoF()){
            archivo->read(buf,1);
            if(*buf!='#'){
                this->header+=&buf[0];
            }
        }
        if(this->header.size()==0)
            return;
        char* separado;
        char tmp[this->header.size()];
        memmove(tmp,this->header.c_str(),this->header.size());
        separado=strtok(tmp,",");
        int tam=atoi((const char*)separado);

        for (int i = 0; i< tam ; i++) {
             separado=strtok(NULL,",");
             string nombre=separado;
             separado=strtok(NULL,",");
             int tipo=atoi((const char*)separado);
             separado=strtok(NULL,",");
             int longitud=atoi((const char*)separado);
             separado=strtok(NULL,",");
             int decimal=atoi((const char*)separado);
             separado=strtok(NULL,",");
             int llave=atoi((const char*)separado);
             Campo* c = new Campo();
             c->crearCampo(nombre,tipo,longitud,decimal,llave);
             this->campos.push_back(c);
         }
    }
}

void Header::setCampos(vector<Campo*> campos){
    this->campos=campos;
}

vector <Campo*> Header::getCampos(){
    return campos;
}
