#include "engine.h"

void resetCamerawindow(GLFWwindow* f, int w, int h)
{
    // LA CAMERA LA CAMERA, ELLE EST BUGGER ET ELLE FAIT NIMPORTE KOI
    glViewport(0, 0, w, h); //x, y --> en haut a gauche; w, h --> largeur et hauteur (Pas coordonnées donc)
}

void engine::init(std::string vertexPath, std::string fragmentPath, uint w, uint h)
{
    engineWindow = window(w, h, "suus");
    engineWindow.init();
    inputPrevent = 0;
    r = g = b = 0.f;
    a = 1.f;
    initGLAD();
    Shader.init(vertexPath, fragmentPath);
    glfwSetFramebufferSizeCallback(engineWindow.getWindow(), resetCamerawindow);
    textureAltas.initAtlas();
}

void engine::setBackgroundColor(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

int engine::initGLAD()
{
    std::cout<<"initialisation GLAD"<<std::endl;
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr<<"ERREUR INI GLAD"<<std::endl;
        return -1;
    }
    std::cout<<"GLAD Initialise"<<std::endl;
    return 0;
}

void engine::keyboardHandler()
{
    
    if(inputPrevent <= 0)
    {
        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(engineWindow.getWindow(), true);
            inputPrevent = 10;
        }

        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            isWireframe = !isWireframe;
            if(isWireframe)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            inputPrevent = 10;
        }
    }

    
}

shader* engine::getShader()
{
    return &Shader;
}

void engine::run()
{
    std::cout<<"--- Debut du rendu ---"<<std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    while(!engineWindow.quit)
    {
       

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f));
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);
        Mesh.rotate(glfwGetTime(), vec3(1.f, 1.f, 1.f));

        //
        Shader.use();
        textureAltas.useTexture(textureAltas.nesCafey);
        Shader.view(view);
        Shader.projection(projection);
        Mesh.draw(&Shader, projection, view);
        engineWindow.update();
        keyboardHandler();
        if(inputPrevent >= 0) inputPrevent--;
    }
    std::cout<<"--- Fin du rendu ---"<<std::endl;
}