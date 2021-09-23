#include "Textures.h"
#include "stb_image.h"
#include "glad.h"
Textures::Textures()
{

}


glm::vec3 random3( glm::vec3 p ) 
{
    glm::vec3 toMult = sin(glm::vec3(
        dot(p,glm::vec3(127.1,311.7, 214.4)),
        dot(p,glm::vec3(269.5,183.3, 107.5)),
        dot(p,glm::vec3(114.5,413.3, 49.5))
        ));

    glm::vec3 toFrac = glm::vec3(toMult.x * 43758.5453, toMult.y * 43758.5453, toMult.z * 43758.5453);

    return glm::vec3(toFrac.x - floor(toFrac.x), toFrac.y - floor(toFrac.y), toFrac.z - floor(toFrac.z));


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
    data.push_back(((F.GetNoise(x, y, z) + 1)/2) * 255);
    data.push_back((worley(glm::vec3((float)x/(float)width, (float)y/(float)height, (float)z/(float)width))) * 255);
}

float Textures::worley(glm::vec3 position)
{
    glm::vec3 st = position;
    st *= 3;
    glm::vec3 i_st = glm::vec3(glm::floor(st.x), glm::floor(st.y), glm::floor(st.z));
    glm::vec3 f_st = glm::vec3(st.x - i_st.x, st.y - i_st.y, st.z  - i_st.z);
    //std::cout<<" I : x = "<<i_st.x<<" y = "<<i_st.y<<" z = "<<i_st.z<<std::endl;
    //std::cout<<" F : x = "<<f_st.x<<" y = "<<f_st.y<<" z = "<<f_st.z<<std::endl;
    float color = 0;

    float minDist = 1;
    

    for(int x = -1; x <= 1; x++)
    {
        for(int y = -1; y <= 1; y++)
        {
            for(int z = -1; z <= 1; z++)
            {
                glm::vec3 voisin = glm::vec3(float(x), float(y), float(z));
                glm::vec3 point = random3(i_st + voisin);
                glm::vec3 diff = (voisin + point) - f_st;
                float dist = glm::length(diff);
                minDist = glm::min(minDist, dist);
            }
        }
    }

    color += minDist;
    /*if(drawPropagation)
    {
        // Draw Propagation
        color -= step(.7,abs(sin(50.0*minDist)))*.3;
    }
    
    if(drawPoint)
    {
        // Draw Points
        color.g += 1.-step(.02, minDist);
    }

    if(drawGrid)
    {
        // Draw grid
        color.r += step(.98, f_st.x) + step(.98, f_st.y);
    }*/

    return color;
}

bool Textures::loadTexture(uint& textures, std::string path)
{
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int width, height, depth, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    width = height = depth = 64;
    nrChannels = 2;
    FastNoise F;
    F.SetNoiseType(FastNoise::NoiseType::Perlin);
    F.SetSeed(42);
    F.SetFractalOctaves(3);
    F.SetFrequency(0.05);
    std::vector<unsigned char> data;
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
