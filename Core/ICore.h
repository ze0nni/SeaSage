/*
 * File:   ICore.h
 * Author: onni
 *
 * Created on 24 Апрель 2012 г., 9:04
 */

#ifndef ICORE_H
#define	ICORE_H

class IDisplay;

class ICore {
public:
    virtual void log(const char* format, ...) = 0;
    virtual void errlog(const char* format, ...) = 0;
    virtual void setActiveDisplay(IDisplay *nextDisplay) = 0;
};

class ICoreObject {
public:
    ICoreObject(ICore *__core) {
        core = __core;
    }

    virtual ~ICoreObject() {}

    ICore* getCore() {
        return core;
    }
private:
    ICore *core;
};

class IDisplay: public ICoreObject {
public:
    IDisplay(ICore *__core): ICoreObject(__core) {

    }

    virtual ~IDisplay() {}
    virtual void doAction(double t) = 0;
    virtual void doRender(double t) = 0;
    //virtual void keyDown(int key) = 0;
    //virtual void keyUp(int key) = 0;
    //virtual void keyPress(int key) = 0;
};


#endif	/* ICORE_H */

