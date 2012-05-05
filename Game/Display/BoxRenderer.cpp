#include "BoxRenderer.h"

BoxRenderer::BoxRenderer(int mask, float bs, float bh)
{
    quads = 5;
    GLfloat x11 = bh;       GLfloat y11 = bh;
    GLfloat x12 = bs-bh;    GLfloat y12 = bh;
    GLfloat x21 = bh;       GLfloat y21 = bs-bh;
    GLfloat x22 = bs-bh;    GLfloat y22 = bs-bh;

    bool bt = mask & BLOCK_FILL_TOP;
    bool br = mask & BLOCK_FILL_RIGHT;
    bool bb = mask & BLOCK_FILL_BOTTOM;
    bool bl = mask & BLOCK_FILL_LEFT;

    if (bt) {
            if (!(bl||br)) {
                y11-=bh;
                y12-=bh;
            }
            quads--;
    }
    if (br) {
            if (!(bt||bb)) {
                x12+=bh;
                x22+=bh;
            }
            quads--;
    }
    if (bb){
            if (!(bl||br)) {
                y21+=bh;
                y22+=bh;
            }
            quads--;
    }
    if (bl){
            if (!(bt||bb)) {
                x11-=bh;
                x21-=bh;
            }
            quads--;
    }
    //Главный квадрат
    V.push_back(x11);   N.push_back(x11);
    V.push_back(bh);     N.push_back(bh);
    V.push_back(y11);   N.push_back(y11);

    V.push_back(x21);   N.push_back(x21);
    V.push_back(bh);     N.push_back(bh);
    V.push_back(y21);   N.push_back(-(bs-y21));

    V.push_back(x22);   N.push_back(-(bs-x22));
    V.push_back(bh);     N.push_back(bh);
    V.push_back(y22);   N.push_back(-(bs-y22));

    V.push_back(x12);   N.push_back(-(bs-x12));
    V.push_back(bh);     N.push_back(bh);
    V.push_back(y12);   N.push_back(y12);

    //боковые гани
    //if (!(mask & BLOCK_FILL_TOP)) {
        V.push_back(0); N.push_back(-bh);
        V.push_back(0); N.push_back(bh);
        V.push_back(0); N.push_back(-bh);

        V.push_back(0); N.push_back(-bh);
        V.push_back(0); N.push_back(bh);
        V.push_back(bs); N.push_back(bh);

        V.push_back(x21); N.push_back(x21);
        V.push_back(bh); N.push_back(bh);
        V.push_back(y21); N.push_back(-(bs-y21));

        V.push_back(x11); N.push_back(x11);
        V.push_back(bh); N.push_back(bh);
        V.push_back(y11); N.push_back(y11);
    //}

    //if (!(mask & BLOCK_FILL_RIGHT)) {
        V.push_back(bs); N.push_back(bh);
        V.push_back(0); N.push_back(bh);
        V.push_back(bs); N.push_back(bh);

        V.push_back(bs); N.push_back(bh);
        V.push_back(0); N.push_back(bh);
        V.push_back(0); N.push_back(-bh);

        V.push_back(x12); N.push_back(-(bs-x12));
        V.push_back(bh); N.push_back(bh);
        V.push_back(y12); N.push_back(y12);

        V.push_back(x22); N.push_back(-(bs-x22));
        V.push_back(bh); N.push_back(bh);
        V.push_back(y22); N.push_back(-(bs-y22));
    //}
    //if (!(mask & BLOCK_FILL_BOTTOM)) {
        V.push_back(0); N.push_back(-bh);
        V.push_back(0); N.push_back(bh);
        V.push_back(bs); N.push_back(bh);

        V.push_back(bs); N.push_back(bh);
        V.push_back(0); N.push_back(bh);
        V.push_back(bs); N.push_back(bh);

        V.push_back(x22); N.push_back(-(bs-x22));
        V.push_back(bh); N.push_back(bh);
        V.push_back(y22); N.push_back(-(bs-y22));

        V.push_back(x21); N.push_back(x21);
        V.push_back(bh); N.push_back(bh);
        V.push_back(y21); N.push_back(-(bs-y21));
    //}
    //if (!(mask & BLOCK_FILL_LEFT)) {
        V.push_back(bs); N.push_back(bh);
        V.push_back(0); N.push_back(bh);
        V.push_back(0); N.push_back(-bh);

        V.push_back(0); N.push_back(-bh);
        V.push_back(0); N.push_back(bh);
        V.push_back(0); N.push_back(-bh);

        V.push_back(x11); N.push_back(x11);
        V.push_back(bh); N.push_back(bh);
        V.push_back(y11); N.push_back(y11);

        V.push_back(x12); N.push_back(-(bs-x12));
        V.push_back(bh); N.push_back(bh);
        V.push_back(y12); N.push_back(y12);
    //}
}

BoxRenderer::~BoxRenderer()
{
    //dtor
}

void BoxRenderer::Render() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, V.data());
    glNormalPointer(GL_FLOAT, 0, N.data());
    glDrawArrays(GL_QUADS, 0, V.size()/3);
}
