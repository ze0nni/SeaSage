#include "Game.h"

Game::~Game()
{
    //dtor
}

void Game::doAction(double t) {
    Uint8 *keys = SDL_GetKeyState(NULL);
    if (player) {
        if (keys[SDLK_UP]) player->moveForward(t);
        if (keys[SDLK_DOWN]) player->moveBack(t);
        if (keys[SDLK_LEFT]) player->rotateLeft(t);
        if (keys[SDLK_RIGHT]) player->rotateRight(t);
        player->doAction(t);
    }
}

void Game::doRender(double t) {

}

void Game::removeHandler(void* g, void* o) {
    ((IGame*)g)->removeObject((IGameObject*)o);
}

void Game::addObject(IGameObject *__obj) {
    __obj->onRemove(this, &removeHandler);
    objects[__obj]=true;
}

void Game::removeObject(IGameObject *__obj) {
    IGameObject *o = (IGameObject*)__obj;
    if (objects.count(o)) {
        objects.erase(o);
    }
}
