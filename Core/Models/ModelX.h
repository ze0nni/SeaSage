#ifndef MODELX_H
#define MODELX_H

#include "../ICore.h"
#include "Model.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

struct FileXHead {
    char signature[3]; //"xof"
    char signatureSpace;
    char HIversion[2];
    char LOversion[2];
    char format[3];    //"txt"
    char formatSpace;
    char floatSize[4]; //размер вещественного числа в битах
    char floatSizeSpace;
};

class ModelX: public Model
{
    public:
        ModelX(ICore *__core);
        virtual ~ModelX();
        bool load(istream *in);
    protected:
    private:
        bool loadTxt(istream *in);
};

#endif // MODELX_H
