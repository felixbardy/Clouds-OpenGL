#ifndef DEF_WINDOW
#define DEF_WINDOW

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class window
{
    public:
    
    window();
    window(int w, int h, const std::string& title);
    ~window();
    int init();
    void update();
    bool quit = false;

    void keyboardHandler();
    GLFWwindow* getWindow();
    

    private:

    int width, height;
    std::string title;
    GLFWwindow* Window;

    int initGlfw(const int & major = 4, const int & minor = 6);
    int initWindow();
    int initGLAD();
    



};

#endif