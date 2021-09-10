#include "textures.h"
#include "stb_image.h"
#include "glad.h"
textures::textures()
{

}

void textures::initAtlas()
{
    

    loadTexture(blockAtlas, "./data/blockAtlas.png");
    loadTexture(nesCafey, "./data/coffeeSquare.jpg");
    loadTexture(cage, "./data/Scage.jpg");
    
}

void textures::useTexture(const uint& texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

bool textures::loadTexture(uint& textures, std::string path)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    float borderColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(data)
    {
        glGenTextures(1, &textures);
        glBindTexture(GL_TEXTURE_2D, textures);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return true;
    }
    else
    {
        std::cerr<<"UNABLE TO LOAD TEXTURE"<<std::endl;
        return false;
    }
}

textures::~textures()
{

}