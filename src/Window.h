#ifndef DEF_WINDOW
#define DEF_WINDOW

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class Window
{
    public:

    Window();
    Window(int w, int h, const std::string& title);
    ~Window();
    int init();
    void update();
    bool quit = false;

    void keyboardHandler();
    GLFWwindow* getWindow();

    int getWidth();
    int getHeight();


    private:

    int width, height;
    std::string title;
    GLFWwindow* Window;

    double xPos, yPos;



    int initGlfw(const int & major = 4, const int & minor = 6);
    int initWindow();
    int initGLAD();




};

#endif
