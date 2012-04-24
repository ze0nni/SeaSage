/* 
 * File:   Display.h
 * Author: onni
 *
 * Created on 24 Апрель 2012 г., 8:51
 */

#include "../ICore.h"

#ifndef DISPLAY_H
#define	DISPLAY_H

class Display : public IDisplay {
public:
    Display(ICore *__core);
    virtual ~Display();
    
    virtual void doAction(double t);
    virtual void doRender(double t);    
private:

};

#endif	/* DISPLAY_H */

