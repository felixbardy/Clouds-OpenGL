#include "World.h"

World::World()
{
    Cam = new Camera();
    projection = glm::mat4(1.f);
}

void World::addNewMeshCube(const Textures& textures)
{
    Mesh * nM = new Mesh();
    nM->setCube(textures, 5);
    glm::vec3 pos = glm::vec3(Meshs.size()%16, 0.f, (Meshs.size()/16)%16);
    pos.y = Meshs.size()/256;
    nM->position.push_back(pos);
    Meshs.push_back(nM);
}

void World::addMesh(Mesh * mesh)
{
    Meshs.push_back(mesh);
}

void World::render(Shader & Shader, float time)
{
    for(int i = 0; i < Meshs.size(); i++)
    {
        Meshs[i]->render(time, Shader, projection, Cam->getViewRef());
    }

}

void World::update()
{
    Cam->update();
}


World::~World()
{
    Cam->~Camera();
    delete Cam;

    for(int i = 0; i < Meshs.size(); i++)
    {
        Meshs[i]->~Mesh();
        delete Meshs[i];
    }
}
