#include "World.h"
#include <GLFW/glfw3.h>
World::World(Textures &tex, Shader &shad): m_textures(tex), m_shader(shad)
{
    std::cout<<"____Initialisation du monde____"<<std::endl;
    m_cam = new Camera();
    m_projection = glm::mat4(1.f);

    Cube * defaultCube = new Cube();
    defaultCube->setShaderKey("basic2D");
    defaultCube->setTextureKeys({"kirbo"});
    addObject(defaultCube);

    //Création du conteneur de nuage
    Object * cloud_container = new Cube();
    cloud_container->setShaderKey("nuage")
                    .setTextureKeys({"shape", "detail", "weathermap"})  
                    .setFaceCulling(false);

    cloud_container->m_position = glm::vec3(2,0,2);

    addObject(cloud_container);
    std::cout<<"Fin de l'initialisation du monde"<<std::endl;
}

void World::addObject(Object * obj)
{
    m_objects.push_back(obj);
}

void World::render()
{
    for(int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->render(m_shader, m_textures, m_cam->getView(), m_projection);
    }
}

void World::update(float time, float ratioScreen)
{
  //y a-t-il un intéret à avoir time et glfwGetTime?
  m_time = glfwGetTime();

  m_projection = glm::perspective(glm::radians(70.f), ratioScreen, 0.1f, 1000.f);

  // Définition des uniforms
  //FIXME Intégrer correctement la définition de la "boite à nuage"

  glm::translate(getCam()->getView(), glm::vec3(-15, 0, 0));

  glm::vec3 box_vmin = glm::vec3(-100.0f, -25.0f, -100.0f);
  glm::vec3 box_vmax = glm::vec3(100.0f, 25.0f, 100.0f);

  glm::mat4 model = glm::mat4(1.f);
  glm::mat4 view = getCam()->getView();
  glm::mat4 projection = m_projection;

  glm::mat4 mvp = projection * view * model;
  glm::mat4 mvpInv = glm::inverse(mvp);

  m_shader.setVec3("nuage", "vmin", box_vmin);
  m_shader.setVec3("nuage","vmax", box_vmax);
  m_shader.setVec3("nuage","lightpos", glm::vec3(0, cos(time) * 70, 0));
  m_shader.setFloat("nuage","lightpower", 100 * ((cos(time / 3.0)/2)+0.5));
  m_shader.setFloat("nuage","lightMultiplicator", 20);

  m_shader.setMat4("nuage","view", getCam()->getViewRef());
  m_shader.setMat4("nuage","projection", m_projection);
  m_shader.setMat4("nuage","mvpMatrix", mvp);
  m_shader.setMat4("nuage","mvpInvMatrix", mvpInv);

  m_shader.setFloat("nuage","time", m_time);
  m_shader.setFloat("nuage","temperature", 10);

  m_shader.setFloat("nuage","globalCoverage", 1.0);
  m_shader.setFloat("nuage","globalDensity", 10.0);
  m_shader.setFloat("nuage","anvilAmount", 0);


  m_cam->update();
}

Camera* World::getCam()
{
    return m_cam;
}

World::~World()
{
    m_cam->~Camera();
    delete m_cam;

    for(int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->~Object();
        delete m_objects[i];
    }
}
