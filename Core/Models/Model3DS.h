#ifndef MODEL3DS_H
#define MODEL3DS_H

#include "../ICore.h"
#include "Model.h"
#include <iostream>

using namespace std;

class Model3DS: public Model
{
    public:
        Model3DS(ICore *__core);
        virtual ~Model3DS();

        bool load(istream *in);
    protected:
    private:
};

#endif // MODEL3DS_H
