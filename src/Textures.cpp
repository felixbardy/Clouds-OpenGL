#include "Textures.h"
#include "stb_image.h"
#include "glad.h"
Textures::Textures()
{

}

void Textures::initAtlas()
{
   
    //F.SetSeed(42);
    glEnable(GL_TEXTURE_3D);
    loadTexture(blockAtlas, "./data/blockAtlas.png");
    //loadTexture(nesCafey, "./data/coffeeSquare.jpg");
    //loadTexture(cage, "./data/Scage.jpg");

}

void Textures::useTexture(const uint& texture)
{
    glBindTexture(GL_TEXTURE_3D, texture);
}
void Textures::fillPoint(int width, int height, int i, int x, int y, int z, FastNoise & F, std::vector<unsigned char> & data)
{
    
    float noise = (F.GetNoise(x, y, z) + 1)/2;
    data[i] = noise * 255;
    if((rand() % width * height * width) < width * height)
    {
        data[i+1] = 255;
    }
    else
    {
        data[i+1] = 0;
    }
    
}

bool Textures::loadTexture(uint& textures, std::string path)
{
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int width, height, depth, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    width = height = depth = 256;
    nrChannels = 2;
    FastNoise F;
    F.SetNoiseType(FastNoise::NoiseType::Perlin);
    F.SetSeed(42);
    F.SetFractalOctaves(3);
    F.SetFrequency(0.05);
    std::vector<unsigned char> data(width * height * depth * nrChannels);
    int x, y, z;
    x = y = z = 0;
    int c = 1;
    int i = 0;

    while(i < width * depth * height * nrChannels)
    {
        fillPoint(width, height, i, x, y, z, F, data);
        x++;
        if(x >= width)
        {
            x = 0;
            y++;
        }
        if(y >= height)
        {
            y = 0;
            z++;
        }
        i+=2;  
    }

    std::cout<<data.size()<<std::endl;
    if(!data.empty())
    {
        glGenTextures(1, &textures);
        glBindTexture(GL_TEXTURE_3D, textures);
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, depth, 0, GL_RG, GL_UNSIGNED_BYTE, &data[0]);
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
