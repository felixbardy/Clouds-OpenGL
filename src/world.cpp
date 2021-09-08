#include "world.h"

world::world()
{
    Mesh = new mesh();
    Cam = new camera();
    projection = glm::mat4(1.f);
}

void world::render(shader & Shader, float time)
{
    Mesh->render(time, Shader, projection, Cam->getView());
}

void world::update()
{
    Cam->update();
}


world::~world()
{
    Mesh->~mesh();
    Cam->~camera();

    delete Mesh;
    delete Cam;
}