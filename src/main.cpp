#include <iostream>
#include "game.h"

int main(int argc, char **argv)
{
    ResourceManager::SetExecutablePath(argv[0]);
    Game g;
    g.Initialization();
    while (!glfwWindowShouldClose(g.GetWindow()))
    {
        g.ProcessInpud();
        g.Render();
    }
    return 0;
}