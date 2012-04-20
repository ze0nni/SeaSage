/* 
 * File:   Core.h
 * Author: onni
 *
 * Created on 20 Апрель 2012 г., 11:23
 */
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <GL/gl.h>
#include <SDL/SDL.h>

#ifndef CORE_H
#define	CORE_H

class Core {
public:
    Core();    
    virtual ~Core();
    void log(const char* format, ...);
    void errlog(const char* format, ...);    
    void init();
    void run();
private:
    bool doGameLoop;
    void gameLoop();
    void doAction(double t);
    void doRender(double t);
};

#endif	/* CORE_H */

