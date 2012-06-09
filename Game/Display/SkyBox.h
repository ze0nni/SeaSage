#ifndef SKYBOX_H
#define SKYBOX_H

#include "GL/gl.h"
#include "../../Core/Models/ModelMesh.h"

class SkyBox: public ModelMesh
{
    public:
        SkyBox(char* texture);
        virtual ~SkyBox();
    protected:
    private:
};

#endif // SKYBOX_H
