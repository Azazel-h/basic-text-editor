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
    this->width = width;
    this->height = height;
    this->title = title;
    this->window = nullptr;
}

int MyWindow::CreateVulkanInstance()
{
    int rc = OK;
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "BTE";
    // appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    // appInfo.pEngineName = "No Engine";
    // appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    createInfo.enabledExtensionCount = glfw_extension_count;
    createInfo.ppEnabledExtensionNames = glfw_extensions;

    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &(this->instance));
    if (result != VK_SUCCESS)
        rc = CREATE_VULKAN_INSTANCE_ERROR;

    return rc;
}

QueueFamilyIndecies FindQueueFamilies(VkPhysicalDevice physical_device)
{
    QueueFamilyIndecies indecies;
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

    int i = 0;
    for (const VkQueueFamilyProperties& queue_family : queue_families)
    {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indecies.graphicsFamily = i;
        }

        if (indecies.is_complete())
            break;
        ++i;
    }
    return indecies;
}


static bool is_device_suitable(VkPhysicalDevice device)
{
    QueueFamilyIndecies indecies = FindQueueFamilies(device);
    return indecies.is_complete();
}


int MyWindow::PickPhysicalDevice()
{
    int rc = OK;
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(this->instance, &device_count, nullptr);
    if (device_count > 0)
    {
        std::vector<VkPhysicalDevice> devices(device_count);
        vkEnumeratePhysicalDevices(this->instance, &device_count, devices.data());
        for (const VkPhysicalDevice& device : devices)
        {
            if (is_device_suitable(device))
            {
                this->physical_device = device;
                break;
            }
        }
        if (this->physical_device == VK_NULL_HANDLE)
            rc = PHYSICAL_DEVICE_NOT_FOUND_ERROR;
    }
    else
        rc = PHYSICAL_DEVICE_NOT_FOUND_ERROR;
    return rc;
}


int MyWindow::CreateLogicalDevice()
{
    int rc = OK;
    QueueFamilyIndecies indecies = FindQueueFamilies(this->physical_device);
    VkDeviceQueueCreateInfo queue_create_info{};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = indecies.graphicsFamily.value();
    queue_create_info.queueCount = 1;

    float queue_priority = 1.0f;
    queue_create_info.pQueuePriorities = &queue_priority;

    VkPhysicalDeviceFeatures device_fatures{};

    VkDeviceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.pQueueCreateInfos = &queue_create_info;
    create_info.queueCreateInfoCount = 1;
    create_info.pEnabledFeatures = &device_fatures;
    create_info.enabledExtensionCount = 0;

    if (vkCreateDevice(this->physical_device, &create_info, nullptr, &(this->device)) != VK_SUCCESS)
        rc = LOGICAL_DEVICE_CREATION_ERROR;

    else
        vkGetDeviceQueue(this->device, indecies.graphicsFamily.value(), 0, &(this->graphics_queue));
    return rc;
}


int MyWindow::InitalizeVulkan()
{
    int rc = OK;
    if ((rc = CreateVulkanInstance()) == OK)
    {
        if ((rc = PickPhysicalDevice()) == OK)
        {
            rc = CreateLogicalDevice();
        }
    }
    return rc;
}

void MyWindow::CleanUpVulkan()
{
    vkDestroyDevice(this->device, nullptr);
    vkDestroyInstance(this->instance, nullptr);
}


int MyWindow::InitializeWindow()
{
    int rc = OK;
    if (glfwInit())
    {
        GLFWwindow* new_window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
        if (new_window)
        {
            this->window = new_window;
            glfwSetErrorCallback(error_callback);
            glfwSetKeyCallback(this->window, key_callback);
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
    this->CleanUpVulkan();
    if (this->window)
    {
        glfwDestroyWindow(this->window);
    }
    glfwTerminate();
}
