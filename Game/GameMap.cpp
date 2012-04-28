#include "GameMap.h"

GameMap::GameMap(IGame *__game): IMap(__game)
{
    cells=0;
    width=0;
    height=0;
    initBlocks();
}

GameMap::~GameMap()
{
    deleteCells();
    deleteBloks();
}

void GameMap::resize(uint newWidth, uint newHeight) {
    if (newHeight==0 || newHeight==0) {
        deleteCells();
        return;
    }
    //Создаем новую карту
    ICell ***newCells = new ICell**[newHeight];
    for (int i=0; i<newHeight; i++) {
        newCells[i] = new ICell*[newWidth];
        for (int j=0; j<newHeight; j++) {
            //Если есть возможность, копируем ячейки со старой карты
            if (i<width && j<height) {
                newCells[i][j] = cells[i][j];
                cells[i][j] = 0;
            } else {
            //Если нет, то создаем новые, пустые
                newCells[i][j] = new GameCell(this);
            }
            switch(rand()%3) {
            case 0:
                newCells[i][j]->setCellType(none);
                break;
            case 1:
                newCells[i][j]->setCellType(water);
                break;
            case 2:
                newCells[i][j]->setCellType(block);
                break;
            }
        }
    }
    //удаляем старую карту
    deleteCells();
    //на ее место ставим новую
    cells = newCells;
    width = newWidth;
    height = newHeight;
}

uint GameMap::getWidth() {
    return width;
}

uint GameMap::getHeight() {
    return height;
}

ICell* GameMap::getCell(uint cx, uint cy) {
}

void GameMap::renderMap(float rx, float ry, int rsize) {
    int cx = (int)(rx/MAP_CELL_SIZE);
    int cy = (int)(ry/MAP_CELL_SIZE);
    int sx = cx-rsize; if (sx<0) sx=0;
    int sy = cy-rsize; if (sy<0) sy=0;
    int ex = cx+rsize; if (ex>width-1) ex=width-1;
    int ey = cy+rsize; if (ey>height-1) ey=height-1;
    glPushMatrix();
    static float r=0.0f;
    glRotatef(r, 0.0f, 1.0f, 0.0f);
    r+=1.0f;
    //сместим на центр
    //glTranslatef(-trsx, 0.0f, -trsy);
    for (int i=sy; i<=ey;i++) {
        glPushMatrix();
        for (int j=sx; j<=ex;j++) {
            switch (cells[i][j]->getCellType()) {
            case block:
                renderBlock(1);
                break;
            case water:
                renderBlock(0);
                break;
            }
            glTranslatef(MAP_CELL_SIZE, 0.0f, 0.0f);
        }
        glPopMatrix();
        glTranslatef(0.0f, 0.0f, MAP_CELL_SIZE);
    }
    glPopMatrix();
}

void GameMap::deleteCells() {
    if (cells) {
        for (int i=0; i<height; i++) {
            for (int j=0; j<height; j++) {
                    if (cells[i][j]) delete cells[i][j];
            }
            delete[] cells[i];
        }
        delete[] cells;
    }
    cells = 0;
    width = 0;
    height = 0;
}

void GameMap::renderBlock(int id) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    GLfloat pVerts[]= {
        0.0f, MAP_BOX_HIGHT*id, 0.0f,
        0.0f, MAP_BOX_HIGHT*id, MAP_CELL_SIZE,
        MAP_CELL_SIZE, MAP_BOX_HIGHT*id, 0.0f,
        MAP_CELL_SIZE, MAP_BOX_HIGHT*id, MAP_CELL_SIZE};
    GLfloat pNormals[]={
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};
    glVertexPointer(3, GL_FLOAT, 0, pVerts);
    glNormalPointer(GL_FLOAT, 0, pNormals);
    if (id) {
        glColor3f(1.0f, 0.8f, 0.0f);
    } else {
        glColor3f(0.0f, 0.8f, 1.0f);
    }
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void GameMap::initBlocks() {

}

void GameMap::deleteBloks() {
}
