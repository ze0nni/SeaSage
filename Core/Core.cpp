/* 
 * File:   Core.cpp
 * Author: onni
 * 
 * Created on 20 Апрель 2012 г., 11:23
 */

#include "Core.h"

Core::Core() {
    log("Core object create");
}

Core::~Core() {
    log("Core object destroy");
}

void Core::init(){
    log("Core::init");
    //todo: SDL_INIT_EVENTTHREAD
    int sdlInitArgs = SDL_INIT_TIMER | SDL_INIT_VIDEO;
    log("SDL_Init(%d)", sdlInitArgs);
    if (SDL_Init(sdlInitArgs) < 0) {
        errlog("SDL_Init() error: %s", SDL_GetError());
        exit(1);
    }    
    //GL SET
    int sdlGlDoubleBuffer = 1;
    int sdlGlRedSize = 5;
    int sdlGlGreenSize = 6;
    int sdlGlBlueSize = 5;
    int sdlGlDepthSize = 24;
    
    log("gl_DoubleBuffer\t%d\t%d\ngl_RedSize\t%d\t%d\ngl_GreenSize\t%d\t%d\ngl_BlueSize\t%d\t%d\ngl_DepthSize\t%d\t%d",
        sdlGlDoubleBuffer, SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, sdlGlDoubleBuffer),
        sdlGlRedSize, SDL_GL_SetAttribute(SDL_GL_RED_SIZE, sdlGlRedSize),
        sdlGlGreenSize, SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, sdlGlGreenSize),
        sdlGlBlueSize, SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, sdlGlBlueSize),
        sdlGlBlueSize, SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, sdlGlDepthSize));
}

void Core::run() {
    log("Core::run");
    int vmWidth = 640;
    int vmHeight = 480;
    int vmDepth = 32;
    int vmFlags = SDL_OPENGL;
    log("SDL_SetVideoMode(%d, %d, %d, %d)",vmWidth, vmHeight, vmDepth, vmFlags);
    
    if (SDL_SetVideoMode(vmWidth, vmHeight, vmDepth, vmFlags) == NULL) {
        errlog("SDL_SetVideoMode() error: %s", SDL_GetError());
        exit(1);
    }
    gameLoop();
}

void Core::setActiveDisplay(IDisplay* nextDisplay) {
    
}

void Core::gameLoop() {
    doGameLoop = true;
    Uint32 lastTick = SDL_GetTicks();
    Uint32 nowTick = SDL_GetTicks();
    double timeDiff = 0.0d;
    do {        
        doAction(timeDiff);
        doRender(timeDiff);
        nowTick = SDL_GetTicks();
        timeDiff = nowTick<=lastTick ? 0.0d : (nowTick-lastTick)/1000.0d;
        lastTick = nowTick;
    } while(doGameLoop);
}

void Core::doAction(double t) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                doGameLoop=false;
                break;                        
        }
    }
}
void Core::doRender(double t) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES); {
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(0.0f, 1.0f);
    } glEnd();
    
    SDL_GL_SwapBuffers();
}

void Core::log(const char* format, ...) {    
    va_list args;
    va_start(args, format);
    
    time_t rawtime;
    time(&rawtime);    
    fprintf(stdout, "=== log === %s", ctime(&rawtime));
    vfprintf(stdout, format, args);        
    fprintf(stdout, "\n\n");
}

void Core::errlog(const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    time_t rawtime;
    time(&rawtime);    
    fprintf(stderr, "=== err === %s", ctime(&rawtime));
    vfprintf(stderr, format, args);        
    fprintf(stderr, "\n\n");
}