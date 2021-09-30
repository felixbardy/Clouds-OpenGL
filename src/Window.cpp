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
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if(m_window == nullptr)
    {
        std::cerr<<"ERREUR CREATION window GLFW"<<std::endl;
        glfwTerminate(); // On termine glfw en cas d'erreur.
        return -1;
    }
    glfwMakeContextCurrent(m_window);
    


    std::cout<<"window GLFW Cree"<<std::endl;
    return 0;
}

GLFWwindow* Window::getWindow()
{
    return m_window;
}

Window::Window()
{
    m_width = 0;
    m_height = 0;
    m_title = "void";
    m_window = nullptr;
}

int Window::getWidth()
{
    glfwGetWindowSize(m_window, &m_width, &m_height);
    return m_width;
}

int Window::getHeight()
{
    glfwGetWindowSize(m_window, &m_width, &m_height);
    return m_height;
}

Window::Window(int w, int h, const std::string& t)
{
    m_width = w;
    m_height = h;
    m_title = t;
    m_window = nullptr;
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
        glfwSwapBuffers(m_window);
        m_quit = glfwWindowShouldClose(m_window);
}

Window::~Window()
{
    
}
