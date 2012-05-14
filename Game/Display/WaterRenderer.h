#ifndef WATERRENDERER_H
#define WATERRENDERER_H

#include <math.h>
#include "../../Core/Math.h"
#include <vector>
#include "GL/gl.h"

#include "../../Core/Models/ModelMesh.h"

class WaterRenderer: public ModelMesh
{
    public:
        WaterRenderer(int mask, float bs, float stepx, float stepy);
        virtual ~WaterRenderer();
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
};

#endif // WATERRENDERER_H
