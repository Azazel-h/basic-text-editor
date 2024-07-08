//
// Created by Yasuhiro on 05.07.2024.
//

#include "window_manager.h"


int main()
{
    int rc = OK;
    char title[] = "Aboba";
    MyWindow manager(600, 400, title);
    if ((rc = manager.InitializeWindow()) == OK)
    {
        if ((rc = manager.InitalizeVulkan()) == OK)
        {
            glfwMakeContextCurrent(manager.window);
            while (!glfwWindowShouldClose(manager.window))
            {
                // glfwPollEvents();
            }
        }
    }
    return rc;
}
