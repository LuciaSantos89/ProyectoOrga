#ifndef HEADER_H
#define HEADER_H

#include "TDAFile.h"
#include "Campo.h"
#include <vector>
#include <sstream>
#include<string.h>
#include <stdlib.h>

class Header
{
public:
    Header();
    void crearHeader(vector<Campo*>);
    void guardarHeader(TDAFile*);
    void recuperarHeader(TDAFile*);
    void setCampos(vector<Campo*>);
    vector<Campo*> getCampos();

private:
    vector<Campo*> campos;
    string header;
};

#endif // HEADER_H
