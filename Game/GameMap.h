
#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <stdlib.h>
#include <math.h>
#include "GL/gl.h"

#include "IGame.h"
#include "GameCell.h"
#include "Display/BoxRenderer.h"
#include "Display/WaterRenderer.h"
#include "Display/WaterSurfaceRenderer.h"
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
        void doAction(double t);

        void renderMap(float rx, float ry, float angle, int rsize);
        void renderBlock(int mask);
    protected:
    private:
        WaterSurfaceRenderer *waterSurface;
        void initWater();
        void deleteWater();
        void renderWater();

        ICell ***cells;
        uint width;
        uint height;
        void deleteCells();

        BoxRenderer* BoxRenderers[15];
        void initBlocks();
        void deleteBloks();
        void enumCells(int sx,int ex, int sy, int ey, void(*proc)(int, ICell*));
};
#endif // GAMEMAP_H
