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
    };
    std::vector<uint> uvI = 
    {/*
      7--4  
     /  /| 764 465
    3--0 5
    |  |/
    2--1
    */
        3, 0, 2, // Devant
        2, 0, 1,

        3, 2, 0, // derriere
        0, 2, 1,

        3, 2, 0, // Gauche
        0, 2, 1,

        3, 0, 2, // droite
        2, 0, 1,

        3, 0, 2, // Haut
        2, 0, 1,

        3, 2, 0, // Bas
        0, 2, 1,
    };
    Test.Mesh.setCube(uv, uvI);
    Test.setBackgroundColor(0.1f, 0.1f, 0.1f, 1.f);
    Test.run();
    return 0;
}