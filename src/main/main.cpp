#include "../app/vulkanapp.h"
#include <iostream>
#include <stdexcept>

int main() 
{
    VulkanApp app;

    try 
    {
        app.excute();
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}