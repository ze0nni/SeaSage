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
    }
}

void Game::doRender(double t) {

}
