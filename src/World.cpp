#include "World.h"

World::World()
{
    m_cam = new Camera();
    m_projection = glm::mat4(1.f);
}

void World::addNewMeshCube(const Textures& textures)
{
    Mesh * nM = new Mesh();
    nM->setCube(textures, 5);
    glm::vec3 pos = glm::vec3(m_meshs.size()%16, 0.f, (m_meshs.size()/16)%16);
    pos.y = m_meshs.size()/256;
    nM->m_position.push_back(pos);
    m_meshs.push_back(nM);
}

void World::addMesh(Mesh * mesh)
{
    m_meshs.push_back(mesh);
}

void World::render(Shader & Shader, float time)
{
    for(int i = 0; i < m_meshs.size(); i++)
    {
        m_meshs[i]->render(time, Shader, m_projection, m_cam->getViewRef());
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

    for(int i = 0; i < m_meshs.size(); i++)
    {
        m_meshs[i]->~Mesh();
        delete m_meshs[i];
    }
}
