#include "GameDisplay.h"

GameDisplay::GameDisplay(IGame *__game):Display(__game->getCore())
{
    game=__game;
    map = new GameMap(__game);
    map->resize(128u, 128u);

    model = new ModelX(__game->getCore());
    model->loadFromFile("src/models/ship.x");
}

GameDisplay::~GameDisplay()
{
    //dtor
}

void GameDisplay::doAction(double t) {
    if (game) game->doAction(t);
}

void GameDisplay::doRender(double t) {
    static GLfloat fogColor[] ={0.8f, 0.9f, 1.0f, 1.0f};

    //Игрок
    IPlayer *p= game->getPlayer();

    //Очистка
    //glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    //Устанавливаем перспективную проекцию
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(75, 800.0f/600.0f, 0.1, 1000);
    gluLookAt(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    //поворот камеры
    //glRotatef(p->getAngle()/M_PI*180.0d, 0.0f, 1.0f, 0.0f);

    //Рисуем карту

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat l0pos[]={0.0f, 4.0f, -2.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, l0pos);

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_START, 4.0f);
    glFogf(GL_FOG_END, 7.0f);

    //Рендер
    float mw = map->getWidth()*map->getCellSize();
    float mh = map->getHeight()*map->getCellSize();

    //Поворачивать будем сцену а не камеру
    //тк иначе будут пробемы с тумано
    glPushMatrix();
    glRotatef(p->getAngle()/M_PI*180.0d, 0.0f, 1.0f, 0.0f);

    //рисование SkyBox
        {
            glDisable(GL_LIGHTING);
            glDepthFunc(GL_ALWAYS);
            glDepthMask(0);
            SkyBox sbox("");
            glColor3fv(fogColor);
            sbox.render(GL_QUADS, RENDER_MESH_NORMALS|RENDER_MESH_UV);
            glDepthFunc(GL_LEQUAL);
            glDepthMask(1);
            glEnable(GL_LIGHTING);
        }

    {
        glPushMatrix();
        glRotatef(-p->getAngle()/M_PI*180.0d, 0.0f, 1.0f, 0.0f);
        glScalef(0.1f, 0.1f, 0.1f);
        //glTranslatef(0.0f, 0.5f, 0.0f);

        glColor3f(0.6f, 0.6f, 0.6f);
        model->render(GL_TRIANGLES, RENDER_MESH_CHILD|RENDER_MESH_NORMALS|RENDER_MESH_TRANSFORM);
        glPopMatrix();


        map->renderMap(
                       p->getPosition()->x,
                       p->getPosition()->z,
                       0.0f,
                       12);
    }
    glPopMatrix();
    //
    glDisable(GL_NORMALIZE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_FOG);
    //Возвращаем старую проекцию
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
