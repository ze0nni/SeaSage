#include "BoxRenderer.h"

BoxRenderer::BoxRenderer(int mask, float bs, float bh)
{
    GLfloat x11 = 0;       GLfloat y11 = 0;
    GLfloat x12 = bs;       GLfloat y12 = 0;
    GLfloat x21 = 0;       GLfloat y21 = bs;
    GLfloat x22 = bs;       GLfloat y22 = bs;

    bool bt = mask & BLOCK_FILL_TOP;
    bool br = mask & BLOCK_FILL_RIGHT;
    bool bb = mask & BLOCK_FILL_BOTTOM;
    bool bl = mask & BLOCK_FILL_LEFT;

    if (!bt) {
            y11-=bh;
            y12-=bh;
    }
    if (!br) {
            x12+=bh;
            x22+=bh;
    }
    if (!bb){
            y21+=bh;
            y22+=bh;
    }
    if (!bl){
            x11-=bh;
            x21-=bh;
    }

    addVertexNormal(0, bh, 0,   0, bh, 0);
    addVertexNormal(0, bh, bs,  0, bh, 0);
    addVertexNormal(bs, bh, bs, 0, bh, 0);
    addVertexNormal(bs, bh, 0,  0, bh, 0);

    if (!bt) {
        addVertexNormal(0, bh, 0,       0, bh, 0);
        addVertexNormal(bs, bh, 0,      0, bh, 0);
        addVertexNormal(x12, -bh, y12,  0, bh, bh);
        addVertexNormal(x11, -bh, y11,  0, bh, bh);
    }
    if (!br) {
        addVertexNormal(bs, bh, 0,      0, bh, 0);
        addVertexNormal(bs, bh, bs,     0, bh, 0);
        addVertexNormal(x22, -bh, y22,  bh, bh, 0);
        addVertexNormal(x12, -bh, y12,  bh, bh, 0);
    }
    if (!bb) {
        addVertexNormal(bs, bh, bs,     0, bh, 0);
        addVertexNormal(0, bh, bs,      0, bh, 0);
        addVertexNormal(x21, -bh, y21,  0, bh, bh);
        addVertexNormal(x22, -bh, y22,  0, bh, bh);
    }
    if (!bl) {
        addVertexNormal(0, bh, bs,      0, bh, 0);
        addVertexNormal(0, bh, 0,       0, bh, 0);
        addVertexNormal(x11, -bh, y11,  -bh, bh, 0);
        addVertexNormal(x21, -bh, y21,  -bh, bh, 0);
    }
}

BoxRenderer::~BoxRenderer()
{
    //dtor
}
