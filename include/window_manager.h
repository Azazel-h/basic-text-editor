//
// Created by Yasuhiro on 06.07.2024.
//

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "rc.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <set>
#include <optional>

struct QueueFamilyIndecies
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool is_complete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};


class MyWindow
{
public:
    MyWindow(int width, int height, char* title);
    ~MyWindow();

    GLFWwindow* window;

    int InitializeWindow();
    int CreateWindowSurface();
    int InitalizeVulkan();
    void CleanUpVulkan();

private:
    int width;
    int height;
    char* title;

    VkInstance instance = VK_NULL_HANDLE;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphics_queue = VK_NULL_HANDLE;
    VkQueue present_queue = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    int CreateVulkanInstance();
    int PickPhysicalDevice();
    int CreateLogicalDevice();
    QueueFamilyIndecies FindQueueFamilies(VkPhysicalDevice physical_device);
    bool is_device_suitable(VkPhysicalDevice device);
};


#endif // WINDOW_MANAGER_H
