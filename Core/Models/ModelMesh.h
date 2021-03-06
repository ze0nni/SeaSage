#ifndef MODELMESH_H
#define MODELMESH_H

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <string.h>

#include "../Math.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

#define RENDER_MESH_NORMALS 1
#define RENDER_MESH_UV 2
#define RENDER_MESH_CHILD 4
#define RENDER_MESH_TRANSFORM 8

class ModelMesh
{
    public:
        ModelMesh();
        virtual ~ModelMesh();
        void addVertex(const float x, const float y, const float z);
        void addVertex(const Vector3d v);
        void addVertexNormal(const float x, const float y, const float z, const float nx, const float ny, const float nz);
        void addVertexNormal(const Vector3d v, const Vector3d n);
        void addVertexUV(const float x, const float y, const float z, const float u, const float v);
        void addVertexUV(const Vector3d v, const Vector3d uv);
        void addVertexNormalUV(const float x, const float y, const float z, const float nx, const float ny, const float nz, const float u, const float v);
        void addVertexNormalUV(const Vector3d v, const Vector3d n, const Vector3d uv);

        void rawAddVertex(const float x, const float y, const float z);
        void rawAddVertex(const Vector3d v);
        void rawAddNormal(const float x, const float y, const float z);
        void rawAddNormal(const Vector3d n);
        void rawAddUV(const float u, const float v);
        void rawAddUV(const Vector3d un);

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

        #define buffersCount 3
        GLuint buffersID[buffersCount];
        bool isModify;
        void doModify() {isModify=true;}
        void noModify() {isModify=false;}
        void genNewBuffer();
};

#endif // MODELMESH_H
