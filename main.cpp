/*
 * File:   main.cpp
 * Author: onni
 *
 * Created on 20 Апрель 2012 г., 11:18
 */

#include <cstdlib>
#include <stdio.h>
#include "Core/Core.h"
#include "Game/Display/MainMenu.h"

using namespace std;

/*
 *
 */

int main(int argc, char** argv) {
    {
        Core core;
        core.init();

        core.setActiveDisplay(new MainMenu(&core));
        core.run();
    }
    return 0;
}

