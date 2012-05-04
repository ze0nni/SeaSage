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
            newCells[i][j]->setCellType(none);
        }
    }
    newCells[7][7]->setCellType(block);
    newCells[6][7]->setCellType(block);
    newCells[8][7]->setCellType(block);
    newCells[7][6]->setCellType(block);
    newCells[7][8]->setCellType(block);
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

    static float ra = 0.0f;
    ra+=0.5f;
    glRotatef(ra, 0, 1, 0);
    glTranslatef(-3.5, 0.0f, -2.5);
    //сместим на центр
    for (int i=sy; i<=ey;i++) {
        glPushMatrix();
        for (int j=sx; j<=ex;j++) {
            switch (cells[i][j]->getCellType()) {
            case block:
                int mask = 0;
                if (i==0 || cells[i-1][j]->getCellType()==block) mask |= BLOCK_FILL_TOP;
                if (j==0 || cells[i][j-1]->getCellType()==block) mask |= BLOCK_FILL_LEFT;
                if (i==height-1 || cells[i+1][j]->getCellType()==block) mask |= BLOCK_FILL_BOTTOM;
                if (j==width-1 || cells[i][j+1]->getCellType()==block) mask |= BLOCK_FILL_RIGHT;
                renderBlock(mask);
                break;
            }
            glDisable(GL_LIGHTING);
            glColor3f(1,0,0);
            glBegin(GL_LINE_LOOP);
            glVertex3f(0,0,0);
            glVertex3f(MAP_CELL_SIZE,0, 0);
            glVertex3f(MAP_CELL_SIZE,0,MAP_CELL_SIZE);
            glVertex3f(0,0,MAP_CELL_SIZE);
            glEnd();
            glColor3f(1,0,0);
            glBegin(GL_LINE_LOOP);
            glVertex3f(0,MAP_BOX_HIGHT,0);
            glVertex3f(MAP_CELL_SIZE,MAP_BOX_HIGHT, 0);
            glVertex3f(MAP_CELL_SIZE,MAP_BOX_HIGHT,MAP_CELL_SIZE);
            glVertex3f(0,MAP_BOX_HIGHT,MAP_CELL_SIZE);
            glEnd();
            glEnable(GL_LIGHTING);

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


    BoxRenderer br(id, MAP_CELL_SIZE, MAP_BOX_HIGHT*2);
    br.Render();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void GameMap::initBlocks() {

}

void GameMap::deleteBloks() {
}
