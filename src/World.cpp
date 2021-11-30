#include "World.h"
#include <GLFW/glfw3.h>
World::World(Textures &tex, Shader &shad): m_textures(tex), m_shader(shad)
{
    std::cout<<"____Initialisation du monde____"<<std::endl;
    m_cam = new Camera();
    m_projection = glm::mat4(1.f);

    //Création du cube de test
    Cube * defaultCube = new Cube(glm::vec3(2.f));
    defaultCube->setShaderKey("basic2D")
                .setFaceCulling(false)
                .setTextureKeys({"sonc", "kirbo"});

    //Création du terrain
    Terrain * beurk = new Terrain();
    beurk->setShaderKey("basic2D")
            .setFaceCulling(false)
            .setTextureKeys({"atlas"});
    //Création du conteneur de nuage
    CloudContainer * CloudBox = new CloudContainer(glm::vec3(0, 0, 0));
    CloudBox->setShaderKey("nuage")
                    .setTextureKeys({"shape", "detail", "weathermap"})  
                    .setFaceCulling(false)
                    .setTextureTypeTo3D();


    CloudBox->m_position = glm::vec3(2,0,2);

    
    addObject(defaultCube);
    addObject(beurk);
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
