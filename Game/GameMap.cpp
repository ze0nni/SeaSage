#include "GameMap.h"

GameMap::GameMap()
{
    //ctor
}

GameMap::~GameMap()
{
    //dtor
}

bool GameMap::resize(uint newWidth, uint newHeight) {
    return false;
}

uint GameMap::getWidth() {
    return width;
}

uint GameMap::getHeight() {
    return height;
}

ICell GameMap::getCell(uint cx, uint cy) {
}
