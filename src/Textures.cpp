#include "Textures.h"
#include "stb_image.h"
#include "glad.h"
Textures::Textures()
{

}

void Textures::initAtlas()
{
   
    //F.SetSeed(42);
    loadTexture(blockAtlas, "./data/blockAtlas.png");
    //loadTexture(nesCafey, "./data/coffeeSquare.jpg");
    //loadTexture(cage, "./data/Scage.jpg");

}

void Textures::useTexture(const uint& texture)
{
    glBindTexture(GL_TEXTURE_3D, texture);
}

bool Textures::loadTexture(uint& textures, std::string path)
{
    //glEnable(GL_BLEND);
    //glEnable(GL_DEPTH);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int width, height, depth, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    width = height = depth = 100;
    FastNoise F;
    F.SetNoiseType(FastNoise::NoiseType::SimplexFractal);
    F.SetSeed(42);
    F.SetFractalOctaves(3);
    F.SetFrequency(0.05);
    std::vector<unsigned char> data;
    int x, y, z;
    x = y = z = 0;
    int c = 1;
    for(int i = 0; i < width * depth * height * 4; i+=4)
    {
        float noise = F.GetNoise(x, y, z);
        
        data.push_back(noise * 255);
        data.push_back(noise * 255);
        data.push_back(noise * 255);
        data.push_back(noise * 255);
 
        x++;
        if(x >= width)
        {
            x = 0;
            y++;
        }

        if(y >= height)
        {
            x = 0;
            y = 0;
            z++;
        }
    }
    
    if(!data.empty())
    {
        glGenTextures(1, &textures);
        glBindTexture(GL_TEXTURE_3D, textures);
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
        glGenerateMipmap(GL_TEXTURE_3D);
        return true;
    }
    else
    {
        std::cerr<<"UNABLE TO LOAD TEXTURE"<<std::endl;
        return false;
    }
}

Textures::~Textures()
{

}
