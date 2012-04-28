#ifndef GAMECELL_H
#define GAMECELL_H

#include "IGame.h"

class GameCell: public ICell
{
    public:
        GameCell(IMap *__map);
        ~GameCell();
    protected:
    private:
};

#endif // GAMECELL_H
