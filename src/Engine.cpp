#include "Engine.h"

void resetCamerawindow(GLFWwindow* f, int w, int h)
{
    // LA CAMERA LA CAMERA, ELLE EST BUGGER ET ELLE FAIT NIMPORTE KOI
    glViewport(0, 0, w, h); //x, y --> en haut a gauche; w, h --> largeur et hauteur (Pas coordonnées donc)
}
void cursorCallback(GLFWwindow * window, double xPos, double yPos)
{
    void *data = glfwGetWindowUserPointer(window);
    Camera * Cam = static_cast<Camera *>(data);
    if (Cam->m_initMouse)
    {
        Cam->setLastX(xPos);
        Cam->setLastY(yPos);
        Cam->m_initMouse = false;
    }
    float xOffset, yOffset;
    xOffset = (xPos - Cam->getLastX()) * Cam->getMouseSensitivity();
    yOffset = (Cam->getLastY() - yPos) * Cam->getMouseSensitivity();
    Cam->setLastX(xPos);
    Cam->setLastY(yPos);
    Cam->m_yawD += xOffset;
    Cam->m_pitchD += yOffset;
    if(Cam->m_pitchD > 89.0f)
        Cam->m_pitchD =  89.0f;
    if(Cam->m_pitchD < -89.0f)
        Cam->m_pitchD = -89.0f;

    glm::vec3 FG;
    FG.x = cos(glm::radians(Cam->m_yawD)); //* cos(glm::radians(Cam->pitchD));
    FG.y = sin(glm::radians(Cam->m_pitchD));
    FG.z = sin(glm::radians(Cam->m_yawD)); //* cos(glm::radians(Cam->pitchD));
    Cam->m_frontMove = normalize(FG);
    Cam->m_front = normalize(glm::vec3(FG.x * cos(glm::radians(Cam->m_pitchD)), FG.y, FG.z * cos(glm::radians(Cam->m_pitchD))));
}
void Engine::init(uint w, uint h)
{
    m_engineWindow = Window(w, h, "suus");
    m_engineWindow.init();
    initGLAD();

    Shapes::initShapes();

    r = g = b = 0.f;
    a = 1.f;
    m_inputPrevent = 0;


    m_shader.init("basic2D", "./shaders/default.vs", "./shaders/default2D.fs");
    m_shader.init("basic3D", "./shaders/default.vs", "./shaders/default3D.fs");
    m_shader.init("nuage", "./shaders/nuage.vs", "./shaders/nuage.fs");


    m_shader.use("basic2D");
    m_shader.setInt("basic2D", "texture1", 0);
    m_shader.setInt("basic2D", "texture2", 1);

    m_shader.use("basic3D");
    m_shader.setInt("basic3D", "texture1", 0);
    m_shader.setInt("basic3D", "texture2", 1);

    m_shader.use("nuage");
    m_shader.setInt("nuage", "shape", 0);
    m_shader.setInt("nuage", "detail", 1);

    m_texturesManager.init();
    m_texturesManager.Load3D("shape", "./data/texture3D/highres.3DT");
    m_texturesManager.Load3D("detail", "./data/texture3D/lowres.3DT");
    m_texturesManager.Load2D("kirbo", "./data/kirbo.png");
    m_texturesManager.Load2D("sonc", "./data/sonc.png");

    m_world = new World(m_texturesManager, m_shader);
    m_world->getCam()->setLastX(w / 2.f);
    m_world->getCam()->setLastY(h / 2.f);
    m_world->m_projection = mat4(1.f);

    glfwSetFramebufferSizeCallback(m_engineWindow.getWindow(), resetCamerawindow);
    glfwSetWindowUserPointer(m_engineWindow.getWindow(), m_world->getCam());
    glfwSetCursorPosCallback(m_engineWindow.getWindow(), cursorCallback);
}
void Engine::setBackgroundColor(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}
int Engine::initGLAD()
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
void Engine::keyboardHandler(Camera * Cam)
{
    float deltaTime = glfwGetTime() - m_lastTime;
    m_lastTime = glfwGetTime();
    float speed = Cam->getSpeed() * deltaTime;
    if(m_inputPrevent <= 0)
    {
        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_engineWindow.getWindow(), true);
            m_inputPrevent = 10;
        }

        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_P) == GLFW_PRESS)
        {
            m_isWireframe = !m_isWireframe;
            if(m_isWireframe)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            m_inputPrevent = 10;
        }

        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_F11) == GLFW_PRESS)
        {
            if(m_isFullscreen)
            {
                glfwSetWindowMonitor(m_engineWindow.getWindow(), glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, 0);
            }
            else
            {
                glfwSetWindowMonitor(m_engineWindow.getWindow(), NULL, 710, 290, 500, 500, 0);
            }

            m_isFullscreen = !m_isFullscreen;
            m_inputPrevent = 10;
                //glfwSetWindowMonitor(m_engineWindow.getWindow(), glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, 60);
        }



        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            if(m_isCursorLocked)
                glfwSetInputMode(m_engineWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            else
                glfwSetInputMode(m_engineWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            m_isCursorLocked = !m_isCursorLocked;
            m_inputPrevent = 10;
        }
    }
     if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            Cam->move(FORWARD, speed);
        }
        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            Cam->move(BACKWARD, speed);
        }
        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            Cam->move(LEFT, speed);
        }
        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            Cam->move(RIGHT, speed);
        }
        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            Cam->move(UP, speed);
        }
        if(glfwGetKey(m_engineWindow.getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            Cam->move(BOTTOM, speed);
        }


}
Shader* Engine::getShader()
{
    return &m_shader;
}

void Engine::run()
{
    glfwSetInputMode(m_engineWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    float time = 0;
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    while(!m_engineWindow.m_quit)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        float ratioScreen = (float)m_engineWindow.getWidth() / (float)m_engineWindow.getHeight();

        m_world->update(time, ratioScreen);
        m_world->render();
        m_engineWindow.update();
        keyboardHandler(m_world->getCam());
        if(m_inputPrevent >= 0) m_inputPrevent--;
    }
}
