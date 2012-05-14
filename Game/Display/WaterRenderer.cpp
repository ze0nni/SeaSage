#include "WaterRenderer.h"

WaterRenderer::WaterRenderer(int mask, float bs, float stepx, float stepy)
{
    //ctor
    int secc = 4;
    float secs = bs/secc;
    float steps = (float)(M_PI*2.0d/secc);
    float h = 0.02f;
    for (int x=0; x<secc; x++) {
            for (int y=0; y<secc; y++) {
                float ox = secs*x;
                float oy = secs*y;

                float h1 = sin(x*steps+stepx)*h;
                float h2 = sin((x+1)*steps+stepx)*h;

                addVertexNormal(ox, h1, oy,             0, h, 0);
                addVertexNormal(ox, h1, oy+secs,        0, h, 0);
                addVertexNormal(ox+secs, h2, oy+secs,   0, h, 0);
                addVertexNormal(ox+secs, h2, oy,        0, h, 0);
            }
    }
}

WaterRenderer::~WaterRenderer()
{
    //dtor
}
