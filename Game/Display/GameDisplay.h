#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include "../../Core/ICore.h"
#include "../../Core/Graphics/Display.h"
#include "../../Core/Models/ModelX.h"

#include "../IGame.h"
#include "../GameMap.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

class GameDisplay: public Display
{
    public:
        GameDisplay(IGame *__game);
        virtual ~GameDisplay();

        void doAction(double t);
        void doRender(double t);
    protected:
    private:
        ModelX *model;
        IGame *game;
        GameMap *map;
};

#endif // GAMEDISPLAY_H
