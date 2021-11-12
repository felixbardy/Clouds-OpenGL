#include "World.h"
#include <GLFW/glfw3.h>
World::World(Textures &tex, Shader &shad): m_textures(tex), m_shader(shad)
{
    std::cout<<"____Initialisation du monde____"<<std::endl;
    m_cam = new Camera();
    m_projection = glm::mat4(1.f);


    //Création du conteneur de nuage
    CloudContainer * CloudBox = new CloudContainer();
    CloudBox->setShaderKey("nuage")
                    .setTextureKeys({"shape", "detail", "weathermap"})  
                    .setFaceCulling(false);

    CloudBox->m_position = glm::vec3(2,0,2);

    addObject(CloudBox);
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
