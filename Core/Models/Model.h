#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>

#include "../ICore.h"
#include "ModelMesh.h"

using namespace std;

class Model
{
    public:
        Model(ICore *__core) {core=__core;};
        virtual ~Model();

        ICore *getCore(){return core;};

        bool loadFromFile(char *filename);
        virtual bool load(istream *in)=0;

        ModelMesh *getRootMesh(){return &rootMesh;};
    protected:
    private:
        ModelMesh rootMesh;
        ICore *core;
};

#endif // MODEL_H
