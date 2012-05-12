#ifndef MODELX_H
#define MODELX_H

#include "../ICore.h"
#include "Model.h"
#include <iostream>

struct FileXHead {
    char Signature[3]; //"xof"
    char space;
    char HIversion[2];
    char LOversion[2];
    char format[3];    //"txt"
};

class ModelX: public Model
{
    public:
        ModelX(ICore *__core);
        virtual ~ModelX();
        bool load(istream *in);
    protected:
    private:
};

#endif // MODELX_H
