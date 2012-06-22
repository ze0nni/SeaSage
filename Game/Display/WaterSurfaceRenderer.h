#ifndef WATERSURFACERENDERER_H
#define WATERSURFACERENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <GL/gl.h>

class WaterSurfaceRenderer
{
    public:
        WaterSurfaceRenderer(int __size);
        virtual ~WaterSurfaceRenderer();
        //
        void render();
        //Пускаем волну
        void pushWave(float x, float y, float mx, float my, float power){};
        //
        void action(double t);
    protected:
    private:
        struct Vector3d {
            float x;
            float y;
            float z;
        };
        struct waveRecord {
            Vector3d *v;
            Vector3d *n;
            Vector3d m; //момент
            Vector3d mSpeed; //скорость
            waveRecord* near[4]; //соседние волны. против часовой стрелки
        };
        //размер квадратного участка
        int size;
        //Поверхность
        std::vector<Vector3d> surfaceVertex;
        std::vector<Vector3d> surfaceNormals;
        std::vector<int> surfaceIndex;
        waveRecord ***waveMap; //карта волн
};

#endif // WATERSURFACERENDERER_H
