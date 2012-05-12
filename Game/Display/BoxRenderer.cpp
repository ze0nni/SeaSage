#include "BoxRenderer.h"

BoxRenderer::BoxRenderer(int mask, float bs, float bh)
{
    quads = 5;
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
            quads--;
    }
    if (!br) {
            x12+=bh;
            x22+=bh;
            quads--;
    }
    if (!bb){
            y21+=bh;
            y22+=bh;
            quads--;
    }
    if (!bl){
            x11-=bh;
            x21-=bh;
            quads--;
    }

    addV(0, bh, 0);     addN(0, bh, 0);
    addV(0, bh, bs);    addN(0, bh, 0);
    addV(bs, bh, bs);   addN(0, bh, 0);
    addV(bs, bh, 0);    addN(0, bh, 0);

    if (!bt) {
        addV(0, bh, 0); addN(0, bh, 0);
        addV(bs, bh, 0); addN(0, bh, 0);
        addV(x12, -bh, y12); addN(0, bh, bh);
        addV(x11, -bh, y11); addN(0, bh, bh);
    }
    if (!br) {
        addV(bs, bh, 0); addN(0, bh, 0);
        addV(bs, bh, bs); addN(0, bh, 0);
        addV(x22, -bh, y22); addN(bh, bh, 0);
        addV(x12, -bh, y12); addN(bh, bh, 0);
    }
    if (!bb) {
        addV(bs, bh, bs); addN(0, bh, 0);
        addV(0, bh, bs); addN(0, bh, 0);
        addV(x21, -bh, y21); addN(0, bh, bh);
        addV(x22, -bh, y22); addN(0, bh, bh);
    }
    if (!bl) {
        addV(0, bh, bs); addN(0, bh, 0);
        addV(0, bh, 0); addN(0, bh, 0);
        addV(x11, -bh, y11); addN(-bh, bh, 0);
        addV(x21, -bh, y21); addN(0-bh, bh, 0);
    }
}

BoxRenderer::~BoxRenderer()
{
    //dtor
}

void BoxRenderer::render() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, V.data());
    glNormalPointer(GL_FLOAT, 0, N.data());
    glDrawArrays(GL_QUADS, 0, V.size()/3);
}


void BoxRenderer::addV(float x, float y, float z) {
    V.push_back(x);
    V.push_back(y);
    V.push_back(z);
}

void BoxRenderer::addN(float x, float y, float z) {
    N.push_back(x);
    N.push_back(y);
    N.push_back(z);
}
