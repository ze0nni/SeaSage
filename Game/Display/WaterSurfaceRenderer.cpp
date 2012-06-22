#include "WaterSurfaceRenderer.h"

WaterSurfaceRenderer::WaterSurfaceRenderer(int __size)
{
    size = __size;
    //карта вершин
    waveMap = new waveRecord**[size+1];
    for (int i=0; i<size+1; i++) {
        waveMap[i] = new waveRecord*[size+1];
        for (int j=0; j<size+1; j++) {
            waveMap[i][j] = new waveRecord();
        }
    }

    //число вершин = (size + 1)^2;
    int vertexCount = (size+1)*(size+1);
    for (int i=0; i<vertexCount; i++) {
        int cx=i%(size+1);
        int cy=i/(size+1);
        //вершина
        Vector3d v;
        v.x=cx;
        v.y=1.0f/(rand()%1000)*10.0f;
        v.z=cy;
        surfaceVertex.push_back(v);
        waveMap[cx][cy]->v = &surfaceVertex[surfaceVertex.size()-1];
        //нормаль
        Vector3d n;
        n.x=0;
        n.y=1;
        n.z=0;
        surfaceNormals.push_back(n);
        waveMap[cx][cy]->n = &surfaceNormals[surfaceNormals.size()-1];
    }
    //число индексов = size^2 * 6

    int indexesCount = size*size;
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            int p1=j+i*(size+1);
            int p2=p1+1;
            int p3=j+(i+1)*(size+1);
            int p4=p3+1;
            //printf("%d:%d\t%d %d %d %d\n", i, j, p1, p2, p3, p4);
            surfaceIndex.push_back(p2);
            surfaceIndex.push_back(p1);
            surfaceIndex.push_back(p3);

            surfaceIndex.push_back(p2);
            surfaceIndex.push_back(p3);
            surfaceIndex.push_back(p4);
        }
    }
}

WaterSurfaceRenderer::~WaterSurfaceRenderer(){
    for (int i=0; i<size+1; i++) {
         for (int j=0; j<size+1; j++) {
            delete waveMap[i][j];
        }
        delete[] waveMap[i];
    }
    delete[] waveMap;
}

void WaterSurfaceRenderer::render() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    //glEnableClientState(GL_INDEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, surfaceVertex.data());
    glNormalPointer(GL_FLOAT, 0, surfaceNormals.data());
    //glIndexPointer(GL_INT, 0, surfaceIndex.data());

    //glDrawArrays(GL_LINE_STRIP, 0, size*size);
    glDrawElements(GL_TRIANGLES, (size+1)*(size+1)*6, GL_UNSIGNED_INT, surfaceIndex.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    //glDisableClientState(GL_INDEX_ARRAY);
}

void WaterSurfaceRenderer::action(double t) {
    for (int i=0; i<size+1; i++) {
        for (int j=0; j<size+1; j++) {
                //printf("%d %d %f\n", i, j, waveMap[i][j]->v->y);
                //waveMap[i][j]->v->y = 0;
        }
    }
}
