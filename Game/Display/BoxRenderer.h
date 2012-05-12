#ifndef BOXRENDERER_H
#define BOXRENDERER_H

#include <vector>
#include "GL/gl.h"

#define BLOCK_FILL_TOP 1
#define BLOCK_FILL_RIGHT 2
#define BLOCK_FILL_BOTTOM 4
#define BLOCK_FILL_LEFT 8

class BoxRenderer
{
    public:
        BoxRenderer(int mask, float bs, float bh);
        virtual ~BoxRenderer();
        void render();
    protected:
    private:
        int quads; //число прямоугольников
        std::vector<GLfloat> V;
        std::vector<GLfloat> N;
        std::vector<GLfloat> UV;
        void addV(float x, float y, float z);
        void addN(float x, float y, float z);
};

#endif // BOXRENDERER_H
