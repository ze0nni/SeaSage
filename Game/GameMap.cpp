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
            switch (random()%4) {
            case 0:
                newCells[i][j]->setCellType(block);
                break;
            default:
                newCells[i][j]->setCellType(water);
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

void drawBlocksproc(int mask, ICell *c) {
    if (c->getCellType()==block) {
        BoxRenderer br(mask, MAP_CELL_SIZE, MAP_BOX_HIGHT*2);
        glColor3f(0.2f, 0.6f, 0.4f);
        br.render(GL_QUADS, RENDER_MESH_NORMALS);
    }
}

void drawWaterproc(int mask, ICell *c) {
    if (c->getCellType()==water) {
    static float step =0.0f;
        step+=0.001f;

        WaterRenderer wr(0, MAP_CELL_SIZE, step, step);

        glColor4f(0.2f, 0.6f, 0.8f, 0.6f);
        wr.render(GL_QUADS, RENDER_MESH_NORMALS);
    }
}

void GameMap::renderMap(float rx, float ry, float angle, int rsize) {

    int cx = (int)(rx/MAP_CELL_SIZE);
    int cy = (int)(ry/MAP_CELL_SIZE);
    int sx = cx-rsize; //if (sx<0) {sx=0;}
    int sy = cy-rsize; //if (sy<0) {sy=0;}
    int ex = cx+rsize; //if (ex>width-1) ex=width-1;
    int ey = cy+rsize; //if (ey>height-1) ey=height-1;
    glPushMatrix();

    //сместим на центр
    float ox; float oy;
    ox=-(rsize) * MAP_CELL_SIZE;
    oy=ox;
    ox-=rx-cx*MAP_CELL_SIZE;
    oy-=ry-cy*MAP_CELL_SIZE;
    glRotated(angle*180.0d/M_PI, 0, 1, 0);
    glTranslatef(ox, 0.0f, oy);
    //Рисуем блоки
    enumCells(sx, ex, sy, ey, &drawBlocksproc);

    //рисуем воду
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    enumCells(sx, ex, sy, ey, &drawWaterproc);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);

    glPopMatrix();
}

void GameMap::enumCells(int sx,int ex, int sy, int ey, void(*proc)(int, ICell*)) {
    glPushMatrix();
    for (int i=sy; i<=ey;i++) {
        glPushMatrix();
        if (i>=0 && i<height)for (int j=sx; j<=ex;j++) {
            if(j>=0 && j<width)
            {
                int mask = 0;
                if (i==0 || cells[i-1][j]->getCellType()==block) mask |= BLOCK_FILL_TOP;
                if (j==0 || cells[i][j-1]->getCellType()==block) mask |= BLOCK_FILL_LEFT;
                if (i==height-1 || cells[i+1][j]->getCellType()==block) mask |= BLOCK_FILL_BOTTOM;
                if (j==width-1 || cells[i][j+1]->getCellType()==block) mask |= BLOCK_FILL_RIGHT;
                proc(mask, cells[i][j]);
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

void GameMap::initBlocks() {

}

void GameMap::deleteBloks() {
}
