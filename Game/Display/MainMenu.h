#ifndef MAINMENU_H
#define MAINMENU_H

#include "../../Core/ICore.h"
#include "../../Core/Graphics/Display.h"

class MainMenu: public Display
{
    public:
        MainMenu(ICore *__core);
        virtual ~MainMenu();

        void doAction(double t);
        void doRender(double t);
    protected:
    private:
};

#endif // MAINMENU_H
