//
// Created by Yasuhiro on 06.07.2024.
//

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "rc.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

class MyWindow {
    public:
        MyWindow(int width, int height, char* title);
        ~MyWindow();

        GLFWwindow* window;

        int InitializeWindow();
        void InitalizeVulkan();
    private:
        int width;
        int height;
        char* title;
        void CreateVulkanInstance();
};


#endif // WINDOW_MANAGER_H