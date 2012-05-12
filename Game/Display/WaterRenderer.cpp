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

                addV(ox, h1, oy);                addN(0, h, 0);
                addV(ox, h1, oy+secs);           addN(0, h, 0);
                addV(ox+secs, h2, oy+secs);      addN(0, h, 0);
                addV(ox+secs, h2, oy);           addN(0, h, 0);
            }
    }
}

WaterRenderer::~WaterRenderer()
{
    //dtor
}

void WaterRenderer::render() {
    glColor4f(0.4f, 0.6f, 1.0f, 0.6f);
    glVertexPointer(3, GL_FLOAT, 0, V.data());
    glNormalPointer(GL_FLOAT, 0, N.data());
    glDrawArrays(GL_QUADS, 0, V.size()/3);
}

void WaterRenderer::addV(float x, float y, float z) {
    V.push_back(x);
    V.push_back(y);
    V.push_back(z);
}

void WaterRenderer::addN(float x, float y, float z) {
    N.push_back(x);
    N.push_back(y);
    N.push_back(z);
}
