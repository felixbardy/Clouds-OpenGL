#include "engine.h"



int main()
{
    engine Test;
    Test.init("./shaders/shader.vs", "./shaders/shader.fs", 500, 500);
    std::vector<float> uv =
    {
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,
        0.f, 1.f,
        
        1.f, 1.f,
        1.f, 0.f,
        0.f, 0.f,
        0.f, 1.f
    };
    Test.Mesh.setCube(uv);
    Test.setBackgroundColor(0.1f, 0.1f, 0.1f, 1.f);
    Test.run();
    return 0;
}