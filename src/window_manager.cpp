//
// Created by Yasuhiro on 06.07.2024.
//

#include "window_manager.h"

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

MyWindow::MyWindow(const int width, const int height, char* title)
{
    MyWindow::width = width;
    MyWindow::height = height;
    MyWindow::title = title;
    window = nullptr;
}

int MyWindow::InitializeWindow()
{
    int rc = OK;
    if (glfwInit())
    {
        GLFWwindow* new_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (new_window)
        {
            window = new_window;
            glfwSetErrorCallback(error_callback);
            glfwSetKeyCallback(window, key_callback);
        }
        else
            rc = GLFW_WINDOW_CREATION_ERROR;
    }
    else
        rc = GLFW_INIT_ERROR;

    return rc;
}

MyWindow::~MyWindow()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}
