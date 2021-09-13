#include "engine.h"

void resetCamerawindow(GLFWwindow* f, int w, int h)
{
    // LA CAMERA LA CAMERA, ELLE EST BUGGER ET ELLE FAIT NIMPORTE KOI
    glViewport(0, 0, w, h); //x, y --> en haut a gauche; w, h --> largeur et hauteur (Pas coordonnées donc)
}
void cursorCallback(GLFWwindow * window, double xPos, double yPos)
{
    void *data = glfwGetWindowUserPointer(window);  
    camera * Cam = static_cast<camera *>(data);
    if (Cam->initMouse)
    {
        Cam->setLastX(xPos);
        Cam->setLastY(yPos);
        Cam->initMouse = false;
    }
    float xOffset, yOffset;
    xOffset = (xPos - Cam->getLastX()) * Cam->getMouseSensitivity();
    yOffset = (Cam->getLastY() - yPos) * Cam->getMouseSensitivity();
    Cam->setLastX(xPos);
    Cam->setLastY(yPos);
    Cam->yawD += xOffset;
    Cam->pitchD += yOffset;
    if(Cam->pitchD > 89.0f)
        Cam->pitchD =  89.0f;
    if(Cam->pitchD < -89.0f)
        Cam->pitchD = -89.0f;

    glm::vec3 FG;
    FG.x = cos(glm::radians(Cam->yawD)) * cos(glm::radians(Cam->pitchD));
    FG.y = sin(glm::radians(Cam->pitchD));
    FG.z = sin(glm::radians(Cam->yawD)) * cos(glm::radians(Cam->pitchD));
    Cam->front = normalize(FG);
}
void engine::init(std::string vertexPath, std::string fragmentPath, uint w, uint h)
{
    engineWindow = window(w, h, "suus");
    engineWindow.init();
    initGLAD();

    World = new world;
    World->Cam->setLastX(w / 2.f);
    World->Cam->setLastY(h / 2.f);
    World->projection = mat4(1.f);
    
    glfwSetFramebufferSizeCallback(engineWindow.getWindow(), resetCamerawindow);
    glfwSetWindowUserPointer(engineWindow.getWindow(), World->Cam);
    glfwSetCursorPosCallback(engineWindow.getWindow(), cursorCallback);  
    textureAltas.initAtlas();

    r = g = b = 0.f;
    a = 1.f;
    inputPrevent = 0;

    Shader.init(vertexPath, fragmentPath);
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

void engine::keyboardHandler(camera * Cam)
{
    float deltaTime = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();
    float speed = Cam->getSpeed() * deltaTime;
    if(inputPrevent <= 0)
    {
        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(engineWindow.getWindow(), true);
            inputPrevent = 10;
        }

        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_P) == GLFW_PRESS)
        {
            isWireframe = !isWireframe;
            if(isWireframe)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            inputPrevent = 10;
        }
    }
     if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            Cam->move(FORWARD, speed);
        }
        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            Cam->move(BACKWARD, speed);
        }
        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            Cam->move(LEFT, speed);
        }
        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            Cam->move(RIGHT, speed);
        }
        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            Cam->move(UP, speed);
        }
        if(glfwGetKey(engineWindow.getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            Cam->move(BOTTOM, speed);
        }

    
}

shader* engine::getShader()
{
    return &Shader;
}

void engine::run()
{   
    std::vector<vec3> position;
    
    float time = 0;
    std::cout<<"--- Debut du rendu ---"<<std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    World->addMesh(textureAltas);
    std::cout<<World->Meshs.size()<<std::endl;
    while(!engineWindow.quit)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        textureAltas.useTexture(textureAltas.blockAtlas);World->projection = glm::perspective(glm::radians(70.f), (float)engineWindow.getWidth() / (float)engineWindow.getHeight(), 0.1f, 100.f);
        
        Shader.use();
        Shader.view(World->Cam->getViewRef());
        Shader.projection(World->projection);

        World->projection = glm::perspective(glm::radians(70.f), (float)engineWindow.getWidth() / (float)engineWindow.getHeight(), 0.1f, 100.f);
        World->update();
        World->render(Shader, glfwGetTime());

        engineWindow.update();
        keyboardHandler(World->Cam);
        if(inputPrevent >= 0) inputPrevent--;
        time+=0.01;
    }
    std::cout<<"--- Fin du rendu ---"<<std::endl;
}