#ifndef IGAME_INCLUDED
#define IGAME_INCLUDED

typedef unsigned int uint;

class ICell;
class IMap;

class IGame {

};

class IMap {
public:
    virtual bool resize(uint newWidth, uint newHeight) = 0;
    virtual uint getWidth()=0;
    virtual uint getHeight()=0;
    virtual ICell getCell(uint cx, uint cy)=0;
};

class ICell {

};

#endif // IGAME_INCLUDED
