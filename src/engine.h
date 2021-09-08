#ifndef DEF_ENGINE
#define DEF_ENGINE

#include <iostream>
#include "glad.h"
#include "window.h"
#include "shader.h"
#include "textures.h"
#include "world.h"
#include <random>

using namespace glm;


class engine
{
    public:
    
    world * World;
    void init(std::string vertexPath, std::string fragmentPath, uint w = 500, uint h = 500);
    void run();
    void close();
    void setBackgroundColor(float r, float g, float b, float a);
    shader* getShader();
    float lastTime = 0;
    textures textureAltas;

    private:

    window engineWindow;
    shader Shader;
    int inputPrevent;
    bool isWireframe = false;
    void keyboardHandler(camera * Cam);

    float r, g, b, a;

    int initGLAD();
};

#endif