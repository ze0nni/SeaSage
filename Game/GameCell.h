#ifndef GAMECELL_H
#define GAMECELL_H

#include "IGame.h"

class GameCell: public ICell
{
    public:
        GameCell(IMap *__map);
        ~GameCell();

        CellType getCellType() {return cellType;};
        void setCellType(CellType __cellType) {cellType=__cellType;}
    protected:
    private:
        CellType cellType;
};

#endif // GAMECELL_H
