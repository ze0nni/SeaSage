/*
 * File:   Core.h
 * Author: onni
 *
 * Created on 20 Апрель 2012 г., 11:23
 */

#ifndef CORE_H
#define	CORE_H

#include "ICore.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <GL/gl.h>
#include <SDL/SDL.h>

class Core : public  ICore {
public:
    Core();
    virtual ~Core();
    void log(const char* format, ...);
    void errlog(const char* format, ...);
    void init();
    void run();
    virtual void setActiveDisplay(IDisplay *nextDisplay);
private:
    IDisplay *activeDisplay;
    bool doGameLoop;
    void gameLoop();
    void doAction(double t);
    void doRender(double t);
};

#endif	/* CORE_H */

