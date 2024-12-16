// #include <vulkan/vulkan.h>
// #include <stdexcept>
// #include <cstdint>
// #include <iostream>
// #include <ostream>
// #include <vector>
// #include <cstring>
// #include <GLFW/glfw3.h>
//
// const uint32_t WINDOW_WIDTH = 800;
// const uint32_t WINDOW_HEIGHT = 600;
//
// #ifdef NDEBUG
// const bool enableValidationLayers = false;
// #else
// const bool enableValidationLayers = true;
// #endif
//
// const std::vector<const char*> validationLayers =
// {
//     "VK_LAYER_KHRONOS_validation",
// };
//
// VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
//                                       const VkAllocationCallbacks* pAllocator,
//                                       VkDebugUtilsMessengerEXT* pDebugMessenger)
// {
//     auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(
//         instance, "vkCreateDebugUtilsMessengerEXT"));
//
//     if (func != nullptr)
//     {
//         return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
//     }
//     else
//     {
//         return VK_ERROR_EXTENSION_NOT_PRESENT;
//     }
// }
//
// void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
//                                    const VkAllocationCallbacks* pAllocator)
// {
//     auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugMessengerEXT");
//
//     if (func != nullptr)
//     {
//         return func(instance, debugMessenger, pAllocator);
//     }
// }
//
// class MyHelloTriangleApplication
// {
// public:
//     void run()
//     {
//         initWindow();
//         initVulkan();
//         mainLoop();
//         cleanup();
//     }
//
// private:
//     GLFWwindow* window;
//     VkInstance instance;
//     VkDebugUtilsMessengerEXT debugMessenger;
//
//     bool checkValidationLayerSupport()
//     {
//         uint32_t layerCount = 0;
//
//         vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
//
//         std::vector<VkLayerProperties> availableLayers(layerCount);
//         vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
//
//         for (const char* layerName : validationLayers)
//         {
//             bool layerFound = false;
//
//             for (const auto& layerProperties : availableLayers)
//             {
//                 if (strcmp(layerName, layerProperties.layerName) == 0)
//                 {
//                     layerFound = true;
//                     break;
//                 }
//             }
//
//             if (!layerFound)
//             {
//                 return false;
//             }
//         }
//
//         return true;
//     }
//
//     void initWindow()
//     {
//         glfwInit();
//         glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//         glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//
//         window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Triangle", nullptr, nullptr);
//     }
//
//     std::vector<const char*> getRequiredExtensions()
//     {
//         uint32_t glfwExtensionCount = 0;
//         const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
//
//         std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
//
//         if (enableValidationLayers)
//         {
//             extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
//         }
//
//         return extensions;
//     }
//
//     static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
//         VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
//         VkDebugUtilsMessageTypeFlagsEXT messageType,
//         const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
//         void* userData
//     )
//     {
//         std::cerr << "Validation layer " << pCallbackData->pMessage << std::endl;
//         return VK_FALSE;
//     }
//
//     void createInstance()
//     {
//         if (enableValidationLayers && !checkValidationLayerSupport())
//         {
//             throw std::runtime_error("Validation layers requested, but not available!");
//         }
//         else
//         {
//             std::cout << "Validation layer requisition return with OK." << std::endl;
//         }
//
//         VkApplicationInfo appInfo = {};
//
//         appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//         appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
//         appInfo.pEngineName = "No Engine";
//         appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
//         appInfo.pApplicationName = "Hello Triangle";
//         appInfo.apiVersion = VK_API_VERSION_1_0;
//
//         auto glfwExtensions = getRequiredExtensions();
//
//         VkInstanceCreateInfo createInfo = {};
//         createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//         createInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensions.size());
//         createInfo.ppEnabledExtensionNames = glfwExtensions.data();
//         createInfo.pApplicationInfo = &appInfo;
//
//         if (enableValidationLayers)
//         {
//             createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//             createInfo.ppEnabledLayerNames = validationLayers.data();
//         }
//         else
//         {
//             createInfo.enabledLayerCount = 0;
//         }
//
//         uint32_t extensionCount = 0;
//         vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//
//         std::vector<VkExtensionProperties> extensions(extensionCount);
//         vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
//
//         std::cout << "Required extensions: " << std::endl;
//
//         for (const auto& extension : glfwExtensions)
//         {
//             std::cout << '\t' << extension << std::endl;
//         }
//
//         std::cout << "Available extensions: " << std::endl;
//
//         for (const auto& extension : extensions)
//         {
//             std::cout << '\t' << extension.extensionName << std::endl;
//         }
//
//         VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
//
//         if (enableValidationLayers)
//         {
//             createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
//             createInfo.ppEnabledLayerNames = validationLayers.data();
//
//             populateDebugMessengerCreateInfo(debugCreateInfo);
//             createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
//         }
//         else
//         {
//             createInfo.enabledLayerCount = 0;
//             createInfo.pNext = nullptr;
//         }
//
//         if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
//         {
//             throw std::runtime_error("Could not create VkInstance");
//         }
//     }
//
//     void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
//     {
//         createInfo = {};
//         createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
//         createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
//             VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
//         createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
//             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
//         createInfo.pfnUserCallback = debugCallback;
//     }
//
//     void setupDebugMessenger()
//     {
//         if (!enableValidationLayers) return;
//
//         VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
//
//         populateDebugMessengerCreateInfo(createInfo);
//
//         if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger))
//         {
//             throw std::runtime_error("Failed to setup debug messenger!");
//         }
//     }
//
//     void initVulkan()
//     {
//         createInstance();
//         setupDebugMessenger();
//     }
//
//     void mainLoop()
//     {
//         while (!glfwWindowShouldClose(window))
//         {
//             glfwPollEvents();
//         }
//     }
//
//     void cleanup()
//     {
//         if (enableValidationLayers)
//         {
//             DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
//         }
//
//         vkDestroyInstance(instance, nullptr);
//         glfwDestroyWindow(window);
//         glfwTerminate();
//     }
// };
//
// int main()
// {
//     MyHelloTriangleApplication app;
//
//     try
//     {
//         app.run();
//     }
//     catch (const std::exception& e)
//     {
//         std::cerr << e.what() << std::endl;
//     }
// }
