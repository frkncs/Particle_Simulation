#include <iostream>
#include <SDL.h>
#include "Window.hpp"

#undef main

using namespace ParticleSimulationEngine;

using namespace std;

int main()
{
    /* TODO 's
    * Screen freezing while dragging (particles still moving and all calculations are fucked up)
    * Make window resizable
    * Add UI
    * Change scale and other values via UI
    */

    Window window;
    window.Run();

	return 0;
}