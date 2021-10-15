#include "World.h"

World::World()
{
    m_cam = new Camera();
    m_projection = glm::mat4(1.f);
}

void World::addNewMeshCube(const std::string & shaderKey, std::vector<std::string> textureKeys, bool is2D)
{
    Mesh * nM = new Mesh();
    nM->setCube();
    if(is2D)
        nM->setTextureTypeTo2D();
    else
        nM->setTextureTypeTo3D();
    nM->setShaderKey(shaderKey);
    nM->setTextureKeys(textureKeys);
    glm::vec3 pos = glm::vec3(m_meshs.size()%16, 0.f, (m_meshs.size()/16)%16);
    pos.y = m_meshs.size()/256;
    nM->m_position.push_back(pos);
    m_meshs.push_back(nM);
}

void World::addMesh(Mesh * mesh)
{
    m_meshs.push_back(mesh);
}

void World::render(Shader & Shader, Textures& textureManager, float time)
{
    for(int i = 0; i < m_meshs.size(); i++)
    {
        m_meshs[i]->render(Shader, textureManager, m_cam->getView(), m_projection, time);
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
