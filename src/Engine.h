#ifndef DEF_ENGINE
#define DEF_ENGINE

#include <iostream>
#include "glad.h"
#include "Window.h"
#include "Shader.h"
#include "Textures.h"
#include "World.h"
#include <random>

using namespace glm;


class Engine
{
    public:

    World * zaWarudo;
    void init(std::string vertexPath, std::string fragmentPath, uint w = 500, uint h = 500);
    void run();
    void close();
    void setBackgroundColor(float r, float g, float b, float a);
    Shader* getShader();
    float lastTime = 0;
    Textures textureAltas;

    private:

    Window engineWindow;
    Shader shader;
    int inputPrevent;
    bool isWireframe = false;
    void keyboardHandler(Camera * Cam);

    float r, g, b, a;

    int initGLAD();
};

#endif
