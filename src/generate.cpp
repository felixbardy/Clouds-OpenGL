#include "Textures.h"

int main(int argc, char*argv[])
{
    std::string name = "";
    bool wrongFormat = false;
    std::cout<<argc<<std::endl;
    if(argc < 5)
    {
        std::cout<<"Erreur : Format invalide"<<std::endl;
        wrongFormat = true;
    }
    else if(argc > 6 && argc < 8)
    {
        std::cout<<"Erreur : Format invalide"<<std::endl;
        wrongFormat = true;
    }

    if(wrongFormat)
    {
        std::cout<<"Les formats valides sont: "<<std::endl<<std::endl;
        std::cout<<"Pour une texture 4CHAN : "<<std::endl;
        std::cout<<"./bin/generate WidthDepthHeight WorleyRes0 WorleyRes1 WorleyRes2 Octaves Seed Frequence (optionel)Nom"<<std::endl<<std::endl;;

        std::cout<<"Pour une texture 3CHAN : "<<std::endl;
        std::cout<<"./bin/generate WidthDepthHeight WorleyRes0 WorleyRes1 WorleyRes2 (optionel)Nom"<<std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        Textures writer;
        int WDH;
        WDH = atoi(argv[1]);
        int WR[3] = {
            atoi(argv[2]),
            atoi(argv[3]),
            atoi(argv[4])
        };
        std::string name = "";
        if(argc <= 6)
        {
            if(argc == 6)
            {
                name = argv[5];
            }
            writer.write3D3Chan(WDH, WR, name);
            std::cout<<"Ecriture d'une texture 3D3CHAN terminer"<<std::endl;
        }
        else
        {
            int O, S, F;
            O = atoi(argv[5]);
            S = atoi(argv[6]);
            F = atoi(argv[7]);
            if(argc == 9)
            {
                name = argv[8];
            }
            writer.write3D4Chan(WDH, WR, O, S, F, name);
            std::cout<<"Ecriture d'une texture 3D4CHAN terminer"<<std::endl;
        }
    }

    return EXIT_SUCCESS;
   
}