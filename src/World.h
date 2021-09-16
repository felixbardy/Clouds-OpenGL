
#ifndef DEF_WORLD
#define DEF_WORLD

#include "Camera.h"
#include "Mesh.h"

class World
{
    public:

    std::vector<Mesh *> Meshs;
    Camera * Cam;
    glm::mat4 projection;

    void addMesh(const Textures& textures);


    void render(Shader & Shader, float time);
    void update();

    World();
    ~World();


};

#endif
