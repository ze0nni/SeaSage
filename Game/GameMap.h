
#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <stdlib.h>
#include <math.h>
#include "GL/gl.h"

#include "IGame.h"
#include "GameCell.h"
#include "Display/BoxRenderer.h"
#include "Display/WaterRenderer.h"
#include "../Core/Models/ModelMesh.h"

#define MAP_CELL_SIZE 0.5f
#define MAP_BOX_HIGHT 0.05f

class GameMap: public IMap
{
    public:
        GameMap(IGame *__game);
        virtual ~GameMap();
        void resize(uint newWidth,uint newHeight);
        uint getWidth();
        uint getHeight();
        ICell* getCell(uint cx, uint cy);
        float getCellSize() {return MAP_CELL_SIZE;}
        //
        void renderMap(float rx, float ry, float angle, int rsize);
    protected:
    private:
        void initWater();
        void deleteWater();
        void renderWater();
        int waterSize;
        float  *waterWave;
        GLfloat *waterVertex;
        GLfloat *waterNormal;
        GLint *waterIndex;

        ICell ***cells;
        uint width;
        uint height;
        void deleteCells();
        void initBlocks();
        void deleteBloks();
        void enumCells(int sx,int ex, int sy, int ey, void(*proc)(int, ICell*));
};
#endif // GAMEMAP_H
