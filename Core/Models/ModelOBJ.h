#ifndef MODELOBJ_H
#define MODELOBJ_H

#include "../ICore.h"
#include "Model.h"
#include <iostream>

class ModelOBJ: public Model
{
    public:
        ModelOBJ(ICore *__core);
        virtual ~ModelOBJ();
    protected:
    private:
};

#endif // MODELOBJ_H
