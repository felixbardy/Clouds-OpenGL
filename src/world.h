
#ifndef DEF_WORLD
#define DEF_WORLD

#include "camera.h"
#include "mesh.h"

class world
{
    public:

    mesh * Mesh;
    camera * Cam;
    glm::mat4 projection;

    void render(shader & Shader, float time);
    void update();

    world();
    ~world();

    
};

#endif