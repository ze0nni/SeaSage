#ifndef IGAME_INCLUDED
#define IGAME_INCLUDED

#include "../Core/ICore.h"

typedef unsigned int uint;

class ICell;
class IMap;

class IGame {
public:
    IGame(ICore *__core) {core=__core;getCore()->log("Game object create");};
    virtual ~IGame() {getCore()->log("Game object destroy");}
    ICore *getCore() {return core;};
private:
    ICore *core;
};

class IMap {
public:
    IMap(IGame *__game) {game=__game;};
    IGame* getGame() {return game;};
    virtual void resize(uint newWidth, uint newHeight) = 0;
    virtual uint getWidth()=0;
    virtual uint getHeight()=0;
    virtual ICell* getCell(uint cx, uint cy)=0;
private:
    IGame *game;
    virtual float getCellSize()=0;
};

enum CellType {
    none,   //Обрыв—будет как падающая вода
    water,  //Вода, для плавания
    block   //блоки для сухопутных крыс
};
class ICell {
public:
    virtual CellType getCellType()=0;
    virtual void setCellType(CellType __cellType)=0;
};

#endif // IGAME_INCLUDED
