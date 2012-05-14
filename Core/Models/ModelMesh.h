#ifndef MODELMESH_H
#define MODELMESH_H

#include <stdio.h>
#include <vector>
#include <GL/gl.h>

#define RENDER_MESH_NORMALS 1
#define RENDER_MESH_UV 2

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
    protected:
    private:
        std::vector<GLfloat> vertex;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> uvCoords;
};

#endif // MODELMESH_H
