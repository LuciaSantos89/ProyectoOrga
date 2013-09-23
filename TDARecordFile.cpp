#include "TDARecordFile.h"

TDARecordFile::TDARecordFile()
{
}

TDARecordFile::~TDARecordFile()
{
}

bool TDARecordFile::addRecord(Registro* r, Index* in){
    string llave=r->campoLLave();
    int offset=this->tell();
    if(!in->verificarIndice(llave))
    {
        string aGuardar=r->convertirAString();
        int tam=0;
        vector<Campo*> campos = r->getCampos();
        for (unsigned int i = 0; i < campos.size(); i++) {
            tam+=campos.at(i)->getLongitud();
        }

        if(AvailList.empty()){
            this->seek(0,ios_base::end);
            offset=this->tell();
        }
        else{
            offset=AvailList.top();
            AvailList.pop();
            this->seek(offset);
        }
        this->write(aGuardar.c_str(),tam);
        this->flush();
        in->agregarIndice(llave,offset);
        return true;
    }
    return false;
}

Registro* TDARecordFile::searchRecord(string llave,vector<Campo*> campos, Index* in){
    string cadenaRegistro="";
    if(in->verificarIndice(llave)){
        Registro* r = new Registro();
        int offset= in->getOffset(llave);
        int tam=0;
        this->seek(offset);
        for (unsigned int i = 0; i < campos.size(); i++) {
            tam+=campos.at(i)->getLongitud();
        }
        char tmp[tam-1];
        this->read(tmp,tam);
        cadenaRegistro=(string) tmp;
        vector<string> registro;
        unsigned int tamCampo1=0;
        unsigned int tamCampo2=0;
        string tmp2="";
        string contCampo="";
        for (unsigned int i = 0; i < campos.size(); i++) {
            tmp2=cadenaRegistro.substr(tamCampo1,campos.at(i)->getLongitud());
            tamCampo1+=campos.at(i)->getLongitud();
            tamCampo2=campos.at(i)->getLongitud();
            for (unsigned int i = 0; i < tamCampo2; i++){
                if(tmp2.at(i)!=' ')
                    contCampo+=tmp2.at(i);
            }
            registro.push_back(contCampo);
            contCampo="";
        }
        r->crearRegistro(registro,campos);
        return r;
    }
    return NULL;
}


bool TDARecordFile::deleteRecord(string llave,Index* in){
    if(in->verificarIndice(llave)){
        int offset= in->getOffset(llave);
        this->seek(offset);
        this->write("&",1);
        this->flush();
        AvailList.push(offset);
        in->eliminarIndice(llave);
        return true;
    }
    return false;
}

vector<Registro*> TDARecordFile::listRecord(vector <Campo*>campos,Index* in){
    string llave="";
    indices=in->getIndices();
    for(map<string,int>::iterator it=indices.begin(); it!=indices.end(); it++){
        llave=it->first;
        Registro* r = this->searchRecord(llave,campos,in);
        registros.push_back(r);
    }
    return registros;
}

void TDARecordFile::guardarIndices(Index* in,string fn){
    string filename=fn.substr(0,fn.size()-5);
    filename+=".ind";
    TDAFile* i=new TDAFile();
    i->open(filename,ios_base::out);
    this->indices=in->getIndices();
    stringstream tmp;
    for(map<string,int>::iterator it=indices.begin(); it!=indices.end(); it++){
        tmp<<setw(15)<<setfill(' ')<<it->first<<setw(5)<<setfill(' ')<<it->second;
        i->write(tmp.str().c_str(),20);
        tmp.str("");
    }
    i->flush();
    i->close();
}

map<string,int> TDARecordFile::abrirIndices(string fn){
    string filename=fn.substr(0,fn.size()-5);
    filename+=".ind";
    TDAFile* i=new TDAFile();
    i->open(filename,ios_base::in);
    i->seek(0,ios_base::beg);
    char tmp[20];
    string indice;
    string llave="";
    int offset=0;
    while(i->eoF()!=true){
        i->read(tmp,20);
        indice=string(tmp);
        for(int j=0;j<15;j++){
            if(indice[j]!=' '){
                llave=indice.substr(j,15-j);
                break;
            }
        }
        offset=atoi(indice.substr(16,5).c_str());
        indices[llave]=offset;
    }
    return this->indices;
}

void TDARecordFile::getAvaillist(int longitudTotal){
    int pos= this->tell();
    this->seek(0,ios_base::end);
    int end=this->tell();
    char cmp[1];
    while(pos<end){
        this->seek(pos);
        this->read(cmp,1);
        if(cmp[0]=='&'){
            AvailList.push(pos);
        }
        pos+=longitudTotal;
    }
}

void TDARecordFile::guardarXML(vector<Campo*> campos, Index* in, string fn){
    string filename=fn.substr(0,fn.size()-5);
    filename+=".xml";
    TDAFile* xmlArchivo=new TDAFile();
    xmlArchivo->open(filename,ios_base::out);
    const char* texto;
    texto="<xml>\n";
    xmlArchivo->write(texto,6);
    xmlArchivo->flush();
    stringstream tmp;
    texto="<campos>\n";
    xmlArchivo->write(texto,9);
    xmlArchivo->flush();
    for(unsigned int i = 0; i<campos.size(); i++){
        tmp<<"<campo nombre=\""<<campos.at(i)->getNombre()
          <<"\" tipo=\""<<campos.at(i)->getTipo()
          <<"\" longitud=\""<<campos.at(i)->getLongitud()
          <<"\" decimal=\""<<campos.at(i)->getDecimal()
         <<"\" llave=\""<<campos.at(i)->getLlave()<<"\" /campo>"<<endl;
    }
    xmlArchivo->write(tmp.str().c_str(),tmp.str().size());
    xmlArchivo->flush();
    texto="</campos>\n";
    xmlArchivo->write(texto,10);
    xmlArchivo->flush();

    vector<Registro*> regs=this->listRecord(campos,in);
    vector <string> registro;
    Registro* r;
    texto="<registros>\n";
    xmlArchivo->write(texto,12);
    xmlArchivo->flush();
    for(unsigned int i=0;i<regs.size();i++){
        stringstream tmp2;
        r=regs.at(i);
        registro=r->getRegistro();
        tmp2<<"<registro ";
        for(unsigned int j=0;j<registro.size();j++){
            tmp2<<campos.at(j)->getNombre()<<"=\""<<registro.at(j)<<"\" ";
        }
        tmp2<<"/registro>"<<endl;
        xmlArchivo->write(tmp2.str().c_str(),tmp2.str().size());
        xmlArchivo->flush();
    }
    texto="</registros>\n";
    xmlArchivo->write(texto,13);
    xmlArchivo->flush();
    texto="</xml>\n";
    xmlArchivo->write(texto,7);
    xmlArchivo->flush();
    xmlArchivo->close();
}
