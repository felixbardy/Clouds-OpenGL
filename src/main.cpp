#include "Engine.h"
#include "Textures.h"


int main(int argc, char*argv[])
{
    if(argc > 1)
    {
        if(argc < 6)
        {
            std::cout<<"Trop peu d'arguments, le format est"<<std::endl;
            std::cout<<"Width-depth-height WorleyResolution Octaves Seed Frequence"<<std::endl;
            return -1;
        }
        Textures Tex;
        Tex.write3D(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
    else
    {
        Engine test;
        test.init("./shaders/nuage.vs", "./shaders/nuage.fs", 500, 500);
        test.setBackgroundColor(0.4f, 0.4f, 0.8f, 1.f);
        test.run();
    }
    return 0;
}
