
#ifndef DEF_WORLD
#define DEF_WORLD

#include "camera.h"
#include "mesh.h"

class world
{
    public:

    std::vector<mesh *> Meshs;
    camera * Cam;
    glm::mat4 projection;

    void addMesh(const textures& textures);
    

    void render(shader & Shader, float time);
    void update();

    world();
    ~world();

    
};

#endif