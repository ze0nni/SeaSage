#ifndef MODEL_H
#define MODEL_H

#include "../ICore.h"
#include <iostream>
#include <fstream>

using namespace std;

class Model
{
    public:
        Model(ICore *__core) {core=__core;};
        virtual ~Model();

        ICore *getCore(){return core;};

        bool loadFromFile(char *filename);
        virtual bool load(istream *in)=0;
    protected:
    private:
        ICore *core;
};

#endif // MODEL_H
