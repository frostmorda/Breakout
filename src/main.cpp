#include <iostream>
#include "game.h"

int main(int argc, char **argv)
{
    ResourceManager::SetExecutablePath(argv[0]);
    Game g(400, 800, "BreakOut");
    g.Initialization();
    while (g.IsWindowClosed())
    {
        g.ProcessInpud();
        g.Render();
    }
    return 0;
}