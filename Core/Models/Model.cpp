#include "Model.h"

Model::~Model()
{
    //dtor
}

bool Model::loadFromFile(char *filename) {
    fstream in;
    in.open(filename, fstream::in);
    if (in.is_open()) {
        getCore()->log("File open %s", filename);
        bool result = load(&in);
        in.close();
        return result;
    }  else {
        getCore()->errlog("File open error %s", filename);
        return false;
    }
}

void Model::render(int glMode, int flags) {
    rootMesh.render(glMode, flags);
}
