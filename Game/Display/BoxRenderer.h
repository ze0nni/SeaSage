#ifndef BOXRENDERER_H
#define BOXRENDERER_H

#include <vector>
#include "GL/gl.h"
#include "../../Core/Models/ModelMesh.h"

#define BLOCK_FILL_TOP 1
#define BLOCK_FILL_RIGHT 2
#define BLOCK_FILL_BOTTOM 4
#define BLOCK_FILL_LEFT 8

class BoxRenderer: public ModelMesh
{
    public:
        BoxRenderer(int mask, float bs, float bh);
        virtual ~BoxRenderer();
    protected:
    private:
};

#endif // BOXRENDERER_H
