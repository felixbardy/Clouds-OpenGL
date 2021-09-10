#include "world.h"

world::world()
{
    Cam = new camera();
    projection = glm::mat4(1.f);
}

void world::addMesh(const textures& textures)
{
    mesh * nM = new mesh();
    nM->setCube(textures);
    
    glm::vec3 pos = glm::vec3(Meshs.size()%16, 0.f, (Meshs.size()/16)%16);
    pos.y = Meshs.size()/256;
    nM->position.push_back(pos);
    Meshs.push_back(nM);
}

void world::render(shader & Shader, float time)
{
    for(int i = 0; i < Meshs.size(); i++)
    {
        Meshs[i]->render(time, Shader, projection, Cam->getViewRef());
    }
    
}

void world::update()
{
    Cam->update();
}


world::~world()
{
    Cam->~camera();
    delete Cam;

    for(int i = 0; i < Meshs.size(); i++)
    {
        Meshs[i]->~mesh();
        delete Meshs[i];
    }
}