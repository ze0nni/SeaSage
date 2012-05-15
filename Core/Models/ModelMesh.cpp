#include "ModelMesh.h"

ModelMesh::ModelMesh()
{
    transformMatrix.setIdentity();
    //ctor
}

ModelMesh::~ModelMesh()
{
    //dtor
}

void ModelMesh::addVertex(float x, float y, float z){
    rawAddVertex(x, y, z);
    rawAddNormal(0.0f, 0.0f, 0.0f);
    rawAddUV(x, z);
}

void ModelMesh::addVertexNormal(float x, float y, float z, float nx, float ny, float nz){
    rawAddVertex(x, y, z);
    rawAddNormal(nx, ny, nz);
    rawAddUV(x, z);
}

void ModelMesh::addVertexUV(float x, float y, float z, float u, float v){
    rawAddVertex(x, y, z);
    rawAddNormal(0.0f, 0.0f, 0.0f);
    rawAddUV(u, v);
}

void ModelMesh::addVertexNormalUV(float x, float y, float z, float nx, float ny, float nz, float u, float v){
    rawAddVertex(x, y, z);
    rawAddNormal(nx, ny, nz);
    rawAddUV(y, v);
}

void ModelMesh::rawAddVertex(float x, float y, float z){
    vertex.push_back(x);
    vertex.push_back(y);
    vertex.push_back(z);
}

void ModelMesh::rawAddNormal(float x, float y, float z){
    normals.push_back(x);
    normals.push_back(y);
    normals.push_back(z);
}

void ModelMesh::rawAddUV(float u, float v){
    uvCoords.push_back(u);
    uvCoords.push_back(v);
}

void ModelMesh::render(int glMode, const int flags) {
    bool drawNormals = (flags & RENDER_MESH_NORMALS) != 0;
    bool drawUV = (flags & RENDER_MESH_UV) != 0;
    bool drawChild = (flags & RENDER_MESH_CHILD) != 0;
    bool doTransform = (flags & RENDER_MESH_TRANSFORM) != 0;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex.data());

    if (drawNormals) {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, 0, normals.data());
    }
    if (drawUV) {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, 0, uvCoords.data());
    }

    if (doTransform) {
        glPushMatrix();
        glMultMatrixf(transformMatrix.data());
    }

    glDrawArrays(glMode, 0, vertex.size()/3);
    if (drawChild) {
        //todo:
    }

    if (doTransform) {
        glPopMatrix();
    }


    if (drawNormals) glDisableClientState(GL_NORMAL_ARRAY);
    if (drawUV) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ModelMesh::addChild(std::string name, ModelMesh* __mesh) {
    if (child.count(name)) {
        delete child[name];
    }
    child[name] = __mesh;
}
