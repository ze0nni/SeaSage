#include "GameDisplay.h"

GameDisplay::GameDisplay(IGame *__game):Display(__game->getCore())
{
    map = new GameMap(__game);
    map->resize(64u, 64u);
}

GameDisplay::~GameDisplay()
{
    //dtor
}

void GameDisplay::doAction(double t) {

}

void GameDisplay::doRender(double t) {
    //Очистка
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //Устанавливаем перспективную проекцию
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(75, 800/600, 0.1, 1000);
    gluLookAt(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    //Рисуем карту
    glMatrixMode(GL_MODELVIEW);
    map->renderMap(0.0f, 0.0f, 5);

    //Возвращаем старую проекцию
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
