//
// Created by Yasuhiro on 05.07.2024.
//
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "errors.h"
#include <iostream>

static void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
    int rc = OK;
    if (glfwInit())
    {
        glfwSetErrorCallback(error_callback);
        GLFWwindow* window = glfwCreateWindow(640, 480, "TextEditor", nullptr, nullptr);
        if (window)
        {
            glfwSetKeyCallback(window, key_callback);
            glfwMakeContextCurrent(window);
            while(!glfwWindowShouldClose(window))
            {
                glfwPollEvents();
                glfwSwapBuffers(window);
            }
            glfwDestroyWindow(window);
            glfwTerminate();
        }
        else
            rc = GLFW_WINDOW_CREATION_ERROR;
    }
    else
        rc = GLFW_INIT_ERROR;

    return rc;
}