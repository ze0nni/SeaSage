
#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <stdlib.h>
#include "GL/gl.h"

#include "IGame.h"
#include "GameCell.h"

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
        void renderMap(float rx, float ry, int rsize);
    protected:
    private:
        ICell ***cells;
        uint width;
        uint height;
        void deleteCells();
        void renderBlock(int id);
        void initBlocks();
        void deleteBloks();
};

#endif // GAMEMAP_H
