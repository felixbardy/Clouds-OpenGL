#ifndef DEF_TEXTURES
#define DEF_TEXTURES
#include <string>
#include <iostream>
#include "stb_image.h"
class textures
{
    public:

    textures();
    ~textures();
    void initAtlas();
    void useTexture(const uint& texture);
    uint blockAtlas;
    uint nesCafey;
    bool loadTexture(uint& texture, std::string path);
    
    
    private:

};


#endif