#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

int main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW failed to init\n";
        return 1;
    }

    std::cout << "GLFW: " << glfwGetVersionString() << "\n";
    glfwTerminate();
}