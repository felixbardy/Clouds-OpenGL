#include "Textures.h"

int main(int argc, char*argv[])
{
    std::string name = "";
    bool wrongFormat = false;
    std::cout<<argc<<std::endl;
    if(argc < 6)
    {
        std::cout<<"Erreur : Format invalide"<<std::endl;
        wrongFormat = true;
    }
    else if(argc > 7 && argc < 9)
    {
        std::cout<<"Erreur : Format invalide"<<std::endl;
        wrongFormat = true;
    }

    if(wrongFormat)
    {
        std::cout<<"Les formats valides sont: "<<std::endl<<std::endl;
        std::cout<<"Pour une texture 4CHAN : "<<std::endl;
        std::cout<<"./bin/generate WidthDepthHeight WorleyRes0 WorleyRes1 WorleyRes2 WorleySeed Octaves Seed Frequence (optionel)Nom"<<std::endl<<std::endl;;

        std::cout<<"Pour une texture 3CHAN : "<<std::endl;
        std::cout<<"./bin/generate WidthDepthHeight WorleyRes0 WorleyRes1 WorleyRes2 WorleySeed (optionel)Nom"<<std::endl;
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
        int worleySeed = atoi(argv[5]);
        std::cout<<worleySeed<<std::endl;
        std::string name = "";
        if(argc <= 7)
        {
            if(argc == 7)
            {
                name = argv[6];
            }
            writer.write3D3Chan(WDH, WR, worleySeed, name);
            std::cout<<"Ecriture d'une texture 3D3CHAN terminer"<<std::endl;
        }
        else
        {
            int O, S, F;
            O = atoi(argv[6]);
            S = atoi(argv[7]);
            F = atoi(argv[8]);
            if(argc == 10)
            {
                name = argv[9];
            }
            writer.write3D4Chan(WDH, WR, worleySeed, O, S, F, name);
            std::cout<<"Ecriture d'une texture 3D4CHAN terminer"<<std::endl;
        }
    }

    return EXIT_SUCCESS;
   
}