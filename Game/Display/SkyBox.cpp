#include "SkyBox.h"

SkyBox::SkyBox(char* texture)
{
    //ctor

    //bottom
    addVertexNormal(-1, -1, -1,     0, 1, 0);
    addVertexNormal(-1, -1,  1,     0, 1, 0);
    addVertexNormal( 1, -1,  1,     0, 1, 0);
    addVertexNormal( 1, -1, -1,     0, 1, 0);
    //top

    //left
    addVertexNormal(-1,  1, -1,     1, 0, 0);
    addVertexNormal(-1,  1,  1,     1, 0, 0);
    addVertexNormal(-1, -1,  1,     1, 0, 0);
    addVertexNormal(-1, -1, -1,     1, 0, 0);
    //right
    addVertexNormal( 1,  1, -1,     -1, 0, 0);
    addVertexNormal( 1, -1, -1,     -1, 0, 0);
    addVertexNormal( 1, -1,  1,     -1, 0, 0);
    addVertexNormal( 1,  1,  1,     -1, 0, 0);
    //back
    addVertexNormal(-1,  1,  1,      0, 0, -1);
    addVertexNormal( 1,  1,  1,      0, 0, -1);
    addVertexNormal( 1, -1,  1,      0, 0, -1);
    addVertexNormal(-1, -1,  1,      0, 0, -1);
    //front
    addVertexNormal(-1,  1, -1,      0, 0, 1);
    addVertexNormal(-1, -1, -1,      0, 0, 1);
    addVertexNormal( 1, -1, -1,      0, 0, 1);
    addVertexNormal( 1,  1, -1,      0, 0, 1);
}

SkyBox::~SkyBox()
{
    //dtor
}
