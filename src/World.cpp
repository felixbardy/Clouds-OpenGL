#include "World.h"

World::World(Textures &tex, Shader &shad): m_textures(tex), m_shader(shad)
{
    m_cam = new Camera();
    m_projection = glm::mat4(1.f);

    addNewMeshCube("basic3D", {"nuage1", "nuage2"});
    addNewMeshCube("basic2D", {"cage", "ulfricZemmour"}, true);
}

void World::addObject(Object * obj)
{
    m_objects.push_back(obj);
}

void World::render(Shader & Shader, Textures& textureManager, float time)
{
    for(int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->render(Shader, textureManager, m_cam->getView(), m_projection, time);
    }
}

void World::update()
{
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
