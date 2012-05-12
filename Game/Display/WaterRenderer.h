#ifndef WATERRENDERER_H
#define WATERRENDERER_H

#include <math.h>
#include "../../Core/Math.h"
#include <vector>
#include "GL/gl.h"


class WaterRenderer
{
    public:
        WaterRenderer(int mask, float bs, float stepx, float stepy);
        virtual ~WaterRenderer();
        void render();
    protected:
    private:
        class WaveVertex: public Vector3d {
        public:
            WaveVertex(WaveVertex* _top,
                       WaveVertex* _right,
                       WaveVertex* _bottom,
                       WaveVertex* _left) {
            }
        };

        int quads; //число прямоугольников
        std::vector<GLfloat> V;
        std::vector<GLfloat> N;
        std::vector<GLfloat> UV;
        void addV(float x, float y, float z);
        void addN(float x, float y, float z);
};

#endif // WATERRENDERER_H
