#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_keyboard.h>

#include "../Core/ICore.h"
#include "IGame.h"

class Game: public IGame
{
    public:
        Game(ICore* __core) : IGame(__core){}
        virtual ~Game();
        void doAction(double t);
        void doRender(double t);
    protected:
    private:
};

#endif // GAME_H
