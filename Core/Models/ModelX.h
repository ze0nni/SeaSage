#ifndef MODELX_H
#define MODELX_H

#include "../ICore.h"
#include "Model.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../Script/TextParser.h"
#include "../Math.h"

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

class ModelXParser;

class ModelX: public Model
{
    public:
        ModelX(ICore *__core);
        virtual ~ModelX();
        bool load(istream *in);
    protected:
    private:
        bool loadTxt(istream *in);

        bool readFrameBlock(TextParser *p, ModelMesh* parent);
        bool readVector(TextParser *p, Vector3d &v);
        bool readMatrix(TextParser *p, Matrix4d &m);
        bool readMesh(TextParser *p, ModelMesh* mesh);
        bool readMeshMaterialList(TextParser *p, ModelMesh* mesh);
};

#endif // MODELX_H
