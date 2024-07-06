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
#include <vector>
#include <optional>

struct QueueFamilyIndecies {
    std::optional<uint32_t> graphicsFamily;

    bool is_complete() {
        return graphicsFamily.has_value();
    }
};
QueueFamilyIndecies FindQueueFamilies(VkPhysicalDevice physical_device);

class MyWindow {
    public:
        MyWindow(int width, int height, char* title);
        ~MyWindow();

        GLFWwindow* window;

        int InitializeWindow();
        int InitalizeVulkan();
    private:
        int width;
        int height;
        char* title;

        VkInstance instance = VK_NULL_HANDLE;
        VkPhysicalDevice physical_device = VK_NULL_HANDLE;
        VkDevice device = VK_NULL_HANDLE;
        VkQueue graphics_queue = VK_NULL_HANDLE;
        int CreateVulkanInstance();
        int PickPhysicalDevice();
        int CreateLogicalDevice();
        void CleanUpVulkan();
};


#endif // WINDOW_MANAGER_H