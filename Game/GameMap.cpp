#include "GameMap.h"

GameMap::GameMap(IGame *__game): IMap(__game)
{
    cells=0;
    width=0;
    height=0;
}

GameMap::~GameMap()
{
    deleteCells();
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
        }
    }
    //удаляем старую карту
    deleteCells();
    //на ее место ставим новую
    cells = newCells;
    width = newWidth;
    height = newHeight;
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

uint GameMap::getWidth() {
    return width;
}

uint GameMap::getHeight() {
    return height;
}

ICell GameMap::getCell(uint cx, uint cy) {
}

void GameMap::renderMap(float rx, float ry, int rsize) {
    int cx = (int)(rx/MAP_CELL_SIZE);
    int cy = (int)(ry/MAP_CELL_SIZE);
    int sx = cx-rsize; if (sx<0) sx=0;
    int sy = cy-rsize; if (sy<0) sy=0;
    int ex = cx+rsize; if (ex>width-1) ex=width-1;
    int ey = cy+rsize; if (ey>height-1) ey=height-1;
    glPushMatrix();
    //сместим на центр
    //glTranslatef(-trsx, 0.0f, -trsy);
    for (int i=sy; i<=ey;i++) {
        glPushMatrix();
        for (int j=sx; j<=ex;j++) {
            glColor3f(1, 0, 0);
            //glRectf(0,0, MAP_CELL_SIZE, MAP_CELL_SIZE);
            {
                glBegin(GL_LINE_LOOP);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, MAP_CELL_SIZE);
                glVertex3f(MAP_CELL_SIZE, 0.0f, MAP_CELL_SIZE);
                glVertex3f(MAP_CELL_SIZE, 0.0f, 0.0f);
                glEnd();
            }
            glTranslatef(MAP_CELL_SIZE, 0.0f, 0.0f);
        }
        glPopMatrix();
        glTranslatef(0.0f, 0.0f, MAP_CELL_SIZE);
    }
    glPopMatrix();
}
