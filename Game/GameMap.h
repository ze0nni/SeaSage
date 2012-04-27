#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "IGame.h"

class GameMap: public IMap
{
    public:
        GameMap();
        virtual ~GameMap();
        bool resize(unsigned int newWidth,unsigned  int newHeight);
    protected:
    private:
};

#endif // GAMEMAP_H
