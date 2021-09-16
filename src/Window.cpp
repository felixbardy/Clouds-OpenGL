#include "Window.h"

int Window::initGlfw(const int & major, const int & minor)
{
    std::cout<<"initialisation GLFW"<<std::endl;
    // initialisation
    if(glfwInit() == GLFW_TRUE)
    {
        // Configuration
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); // Version majeur d'openGL (1 2 3 4)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor); // Version précise de la majeur (le 8 de 4.8 par ex)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        std::cout<<"GLFW Initilise"<<std::endl;
        return 0;
    }
    else
    {
        std::cerr<<"ERREUR INITIALISATION GLFW"<<std::endl;
        return -1;
    }

}



int Window::initWindow()
{
    std::cout<<"Creation de la window GLFW"<<std::endl;
    Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(Window == nullptr)
    {
        std::cerr<<"ERREUR CREATION window GLFW"<<std::endl;
        glfwTerminate(); // On termine glfw en cas d'erreur.
        return -1;
    }
    glfwMakeContextCurrent(Window);
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    std::cout<<"window GLFW Cree"<<std::endl;
    return 0;
}

GLFWwindow* Window::getWindow()
{
    return Window;
}

Window::Window()
{
    width = 0;
    height = 0;
    title = "void";
    Window = nullptr;
}

int Window::getWidth()
{
    glfwGetWindowSize(Window, &width, &height);
    return width;
}

int Window::getHeight()
{
    glfwGetWindowSize(Window, &width, &height);
    return height;
}

Window::Window(int w, int h, const std::string& t)
{
    std::cout<<"construction window"<<std::endl;
    width = w;
    height = h;
    title = t;
    Window = nullptr;
    std::cout<<"fin construction window"<<std::endl;
}

int Window::init()
{
    std::cout<<"--- Initilisation de la window ---"<<std::endl;
    if(initGlfw() < 0) return -1;
    if(initWindow() > 0) return -2;

    std::cout<<"-- Fin de l'initialisation ---"<<std::endl;
    return 0;
}

void Window::update()
{
        // Callback et evenement
        glfwPollEvents();
        glfwSwapBuffers(Window);
        quit = glfwWindowShouldClose(Window);
}

Window::~Window()
{
}
