#include "Textures.h"

int main(int argc, char*argv[])
{
    std::string name = "";
    if(argc < 6)
    {
        std::cout<<"Trop peu d'arguments, le format est"<<std::endl;
        std::cout<<"Width-depth-height WorleyResolution Octaves Seed Frequence (optional)Name"<<std::endl;
        return -1;
    }
    else if(argc > 6)
    {
        name = argv[6];
    }
    Textures Tex;
    Tex.write3D(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), name);
}