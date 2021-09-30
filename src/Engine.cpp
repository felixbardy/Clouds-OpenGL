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
    FG.x = cos(glm::radians(Cam->yawD)); //* cos(glm::radians(Cam->pitchD));
    FG.y = sin(glm::radians(Cam->pitchD));
    FG.z = sin(glm::radians(Cam->yawD)); //* cos(glm::radians(Cam->pitchD));
    Cam->frontMove = normalize(FG);
    Cam->front = normalize(glm::vec3(FG.x * cos(glm::radians(Cam->pitchD)), FG.y, FG.z * cos(glm::radians(Cam->pitchD))));
}
void Engine::init(std::string vertexPath, std::string fragmentPath, uint w, uint h)
{
    m_window = Window(w, h, "suus");
    m_window.init();
    initGLAD();

    zaWarudo = new World;
    zaWarudo->Cam->setLastX(w / 2.f);
    zaWarudo->Cam->setLastY(h / 2.f);
    zaWarudo->projection = mat4(1.f);

    glfwSetFramebufferSizeCallback(m_window.getWindow(), resetCamerawindow);
    glfwSetWindowUserPointer(m_window.getWindow(), zaWarudo->Cam);
    glfwSetCursorPosCallback(m_window.getWindow(), cursorCallback);

		m_tabTextures = new Textures();
		//m_tabTextures->generate3DWorley();
    m_tabTextures->loadTexture("./data/blockAtlas.png");

    r = g = b = 0.f;
    a = 1.f;
    inputPrevent = 0;

    shader.init(vertexPath, fragmentPath);
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
    float deltaTime = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();
    float speed = Cam->getSpeed() * deltaTime;
    if(inputPrevent <= 0)
    {
        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_window.getWindow(), true);
            inputPrevent = 10;
        }

        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_P) == GLFW_PRESS)
        {
            isWireframe = !isWireframe;
            if(isWireframe)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            inputPrevent = 10;
        }

        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_F11) == GLFW_PRESS)
        {
            if(isFullscreen)
            {
                glfwSetWindowMonitor(m_window.getWindow(), glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, 0);
            }
            else
            {
                glfwSetWindowMonitor(m_window.getWindow(), NULL, 710, 290, 500, 500, 0);
            }

            isFullscreen = !isFullscreen;
            inputPrevent = 10;
                //glfwSetWindowMonitor(m_window.getWindow(), glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, 60);
        }



        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            if(isCursorLocked)
                glfwSetInputMode(m_window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            else
                glfwSetInputMode(m_window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            isCursorLocked = !isCursorLocked;
            inputPrevent = 10;
        }
    }
     if(glfwGetKey(m_window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            Cam->move(FORWARD, speed);
        }
        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            Cam->move(BACKWARD, speed);
        }
        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            Cam->move(LEFT, speed);
        }
        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            Cam->move(RIGHT, speed);
        }
        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            Cam->move(UP, speed);
        }
        if(glfwGetKey(m_window.getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            Cam->move(BOTTOM, speed);
        }


}
Shader* Engine::getShader()
{
    return &shader;
}

void Engine::run()
{
    glfwSetInputMode(m_window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    float time = 0;
		//glEnable(GL_CULL_FACE); //uncomment to activate culling
    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    zaWarudo->addNewMeshCube(m_tabTextures);
    std::cout<<"Nombre de mesh : "<<zaWarudo->Meshs.size()<<std::endl;
    while(!m_window.quit)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        m_tabTextures->useTexture();
        zaWarudo->projection = glm::perspective(glm::radians(70.f), (float)m_window.getWidth() / (float)m_window.getHeight(), 0.1f, 1000.f);

        shader.use();

        // Définition des uniforms
        //FIXME Intégrer correctement la définition de la "boite à nuage"
        vec3 box_vmin = vec3(-50.0f, -25.0f, -50.0f);
        vec3 box_vmax = vec3(50.0f, 25.0f, 50.0f);

        mat4 model = mat4(1.f);
        mat4 view = zaWarudo->Cam->getView();
        mat4 projection = zaWarudo->projection;

        mat4 mvp = projection * view * model;
        mat4 mvpInv = glm::inverse(mvp);

        shader.setVec3("vmin", box_vmin);
        shader.setVec3("vmax", box_vmax);
        shader.setVec3("lightpos", vec3(
                            cos(time) * 60,
                            0,
                            sin(time) * 60
                            )
                        );
        shader.setFloat("lightpower", 100);

        shader.setMat4("view", zaWarudo->Cam->getViewRef());
        shader.setMat4("projection", zaWarudo->projection);
        shader.setMat4("mvpMatrix", mvp);
        shader.setMat4("mvpInvMatrix", mvpInv);

        shader.setFloat("time", time);
        shader.setFloat("temperature", 10);


        zaWarudo->update();
        zaWarudo->render(shader, glfwGetTime());

        m_window.update();
        keyboardHandler(zaWarudo->Cam);
        if(inputPrevent >= 0) inputPrevent--;
        time+=0.01;
    }
}
