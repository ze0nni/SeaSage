#ifndef MODELMESH_H
#define MODELMESH_H

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include "../Math.h"

#include <GL/gl.h>

#define RENDER_MESH_NORMALS 1
#define RENDER_MESH_UV 2
#define RENDER_MESH_CHILD 4
#define RENDER_MESH_TRANSFORM 8

class ModelMesh
{
    public:
        ModelMesh();
        virtual ~ModelMesh();
        void addVertex(float x, float y, float z);
        void addVertexNormal(float x, float y, float z, float nx, float ny, float nz);
        void addVertexUV(float x, float y, float z, float u, float v);
        void addVertexNormalUV(float x, float y, float z, float nx, float ny, float nz, float u, float v);

        void rawAddVertex(float x, float y, float z);
        void rawAddNormal(float x, float y, float z);
        void rawAddUV(float u, float v);

        void render(int glMode, const int flags);
        void setTransformMatrix(Matrix4d &m){transformMatrix=m;}
        void addChild(std::string name, ModelMesh* __mesh);
    protected:
    private:
        Matrix4d transformMatrix;
        std::map<std::string, ModelMesh*> child;
        std::vector<GLfloat> vertex;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> uvCoords;
};

#endif // MODELMESH_H
