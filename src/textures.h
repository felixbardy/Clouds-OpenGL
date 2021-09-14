#ifndef DEF_TEXTURES
#define DEF_TEXTURES
#include <string>
#include <iostream>
#include "stb_image.h"
#include <vector>

class textures
{
    public:

    textures();
    ~textures();
    void initAtlas();
    void useTexture(const uint& texture);
    uint blockAtlas;
    uint nesCafey;
    uint cage;
    bool loadTexture(uint& texture, std::string path);

    std::vector<std::vector<uint>> blockTextures = 
    {
        {0, 0, 0, 0, 0, 0}, //Stone
        {5, 5, 5, 5, 6, 6}, // Oak Log
        {10, 10, 10, 10, 10, 10}, //Sand DEV DER G D H B
        {12, 13, 13, 13, 15, 15}
    };


    
    
    private:

};


#endif