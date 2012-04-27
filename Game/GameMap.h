#include "IGame.h"

#ifndef GAMEMAP_H
#define GAMEMAP_H

class GameMap: public IMap
{
    public:
        GameMap();
        virtual ~GameMap();
        bool resize(uint newWidth,uint newHeight);
        uint getWidth();
        uint getHeight();
        ICell getCell(uint cx, uint cy);
    protected:
    private:
        uint width;
        uint height;
};

#endif // GAMEMAP_H
