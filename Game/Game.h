#ifndef GAME_H
#define GAME_H

#include <map>

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

        static void removeHandler(void* g, void* o);
        void addObject(IGameObject *__obj);
        void removeObject(IGameObject *__obj);
    protected:
    private:
        std::map<IGameObject*,bool> objects;
};

#endif // GAME_H
