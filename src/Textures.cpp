#include "Textures.h"
Textures::Textures()
{

}

void Textures::init()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_3D);
}

void Textures::use3D(const std::string& key, uint texNumb)
{
    glActiveTexture(GL_TEXTURE0+texNumb);
    //std::cout<<"GL_TEXTURE"<<texNumb<<std::endl;
    glBindTexture(GL_TEXTURE_3D, m_texId[key]);
}

void Textures::use2D(const std::string& key, uint texNumb)
{
    glActiveTexture(GL_TEXTURE0+texNumb);
    //std::cout<<"GL_TEXTURE"<<texNumb<<std::endl;
    glBindTexture(GL_TEXTURE_2D, m_texId[key]);
}

void Textures::Load2D(const std::string & key, const std::string & path)
{
    std::vector<unsigned char> data;
    uint width, height;


    //decode
    unsigned error = lodepng::decode(data, width, height, path.c_str());

    
    for(int i = 0; i < data.size(); i+=4)
    {
        std::reverse(data.begin()+i, data.begin()+i+4);
    }

    std::reverse(data.begin(), data.end());

    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    m_texId.insert({key, 0});
    glGenTextures(1, &m_texId[key]);
    glBindTexture(GL_TEXTURE_2D, m_texId[key]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Textures::fillPoint(int width, int height, int x, int y, int z, FastNoise & F, Worley & W, std::vector<unsigned char> & data)
{
    data.push_back(((F.GetNoise(x, y, z) + 1)/2) * 255);
    data.push_back(W.get3d(x, y, z) *  255);
}

glm::vec2 curlNoise2D(double x, double y, FastNoise & F)
{
    const float eps = 0.01;
    double n1 = F.GetNoise(x + eps, y);
    double n2 = F.GetNoise(x - eps, y); 

    //Average to find approximate derivative
    double a = (n1 - n2)/(2 * eps);

    //Find rate of change in Y direction
    n1 = F.GetNoise(x, y + eps); 
    n2 = F.GetNoise(x, y - eps); 

    //Average to find approximate derivative
    double b = (n1 - n2)/(2 * eps);

    return glm::vec2(b, -a);
}

double myLerp(double x, double y, double ratio)
{
    return ratio * x + (1-ratio) * y;
}

void Textures::writeTexture(std::ofstream & file, unsigned char data[], const uint & length)
{   
    for(int i = 0; i < length; i++)
    {
        file.write((char *)&data[i], sizeof(unsigned char));
    }
}

void Textures::nextStepTexture(const uint & resolution, const uint & nChan, uint & x, uint & y, uint & z, uint & i)
{
    x++;
    if(x >= resolution)
    {
        x = 0;
        y++;
    }
    if(y >= resolution)
    {
        y = 0;
        z++;
        std::cout<<"etape : "<<z<<" / "<<resolution<<std::endl;
    }
    i+=nChan;
}

bool Textures::createAndLoad3D(const std::string& key)
{
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int width, height, depth, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    width = height = depth = 128;
    nrChannels = 2;
    FastNoise F;
    F.SetNoiseType(FastNoise::NoiseType::Simplex);
    F.SetSeed(42);
    F.SetFractalOctaves(3);
    F.SetFrequency(0.05);
    
    std::vector<unsigned char> data;
    uint x, y, z;
    x = y = z = 0;
    uint i = 0;
    float perlin = (F.GetPerlin(x, y)+1.0)/2.0;
    float angle = (perlin * M_PI * 2);  
    while(i < width * depth * height * nrChannels)
    {
        glm::vec2 curl = (curlNoise2D(x, y, F) + glm::vec2(1, 1))/glm::vec2(2.0, 2.0);
        
        glm::vec2 curlP = curl;
        
        curl.x = curlP.x * cos(angle) - curlP.y * sin(angle);
        curl.y = curlP.x * sin(angle) + curlP.y * cos(angle);
        data.push_back((curl.x + 1)/2.f * 255);
        data.push_back((curl.y + 1)/2.f * 255);
        nextStepTexture(width, nrChannels, x, y, z, i);
    }

    std::cout<<data.size()<<std::endl;
    if(!data.empty())
    {
        m_texId.insert({key, 0});
        glGenTextures(1, &m_texId[key]);
        glBindTexture(GL_TEXTURE_3D, m_texId[key]);
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

bool Textures::write3D4Chan(int WDH, int WR[3], int O, int S, int Fr, std::string name)
{
    int nrChannels = 4;
    FastNoise F;
    F.SetNoiseType(FastNoise::NoiseType::Perlin);
    F.SetSeed(S);
    F.SetFractalOctaves(O);
    F.SetFrequency((float)Fr/(float)100);

    Worley W[3] = 
    {
        Worley(WR[0], WDH, WDH, WDH),
        Worley(WR[1], WDH, WDH, WDH),
        Worley(WR[2], WDH, WDH, WDH),
    };

    std::string path;
    std::cout<<name<<std::endl;
    if(name == "")
    {
        path =
        "./data/texture3D/WHD=" + std::to_string(WDH) +
        "_WR0=" + std::to_string(WR[0]) +
        "_WR1=" + std::to_string(WR[1]) +
        "_WR2=" + std::to_string(WR[2]) +
        "_O=" + std::to_string(O) +
        "_S=" + std::to_string(S) +
        "_F=" + std::to_string(Fr) +
        ".3DT";
    }
    else
    {
        path = "./data/texture3D/" + name + ".3DT";
    }

    std::ofstream data(path, std::ios::out | std::ios::binary);
    if(!data.is_open())
    {
        std::cerr<<"Erreur ouverture fichier"<<std::endl;
        return false;
    }

    uint x, y, z;
    x = y = z = 0;
    uint i = 0;

    while(i < WDH * WDH * WDH * nrChannels)
    {
        unsigned char toFile[4] = {
        (unsigned char)(((1+F.GetNoise(x, y, z))/2.0) * 255),
        (unsigned char)(W[0].get3d(x, y, z) *  255),
        (unsigned char)(W[1].get3d(x, y, z) *  255),
        (unsigned char)(W[2].get3d(x, y, z) *  255)};
        writeTexture(data, toFile, 4);
        nextStepTexture(WDH, nrChannels, x, y, z, i);
    }
    data.write((char * )&WDH, sizeof(char));
    data.write((char * )&nrChannels, sizeof(char));
    data.close();
    return true;
}

const std::vector<std::string> explode(const std::string& s, const char& c)
{
	std::string buff{""};
	std::vector<std::string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

glm::vec3 curlNoise(glm::vec3 p, FastNoise & fast)
{  
    const float e = 1;
    glm::vec3 dx = glm::vec3( e   , 0.0 , 0.0 );
    glm::vec3 dy = glm::vec3( 0.0 , e   , 0.0 );
    glm::vec3 dz = glm::vec3( 0.0 , 0.0 , e   );  

    glm::vec3 pV0 = glm::vec3(  fast.GetNoise(p.x - e, p.y, p.z), 
                                fast.GetNoise(p.x, p.y - e, p.z), 
                                fast.GetNoise(p.x, p.y, p.z - e));

    glm::vec3 pV1 = glm::vec3(  fast.GetNoise(p.x + e, p.y, p.z), 
                                fast.GetNoise(p.x, p.y + e, p.z), 
                                fast.GetNoise(p.x, p.y, p.z + e));

    float x = pV1.z - pV0.z - pV1.y + pV0.y;
    float y = pV1.x - pV0.x - pV1.z + pV0.z;
    float z = pV1.y - pV0.y - pV1.x + pV0.x;

    const float divisor = 1.0 / ( 2.0 * e );
    return glm::normalize( glm::vec3( x , y , z ) * divisor );

}

bool Textures::write3D3Chan(int WDH, int WR[3], std::string name)
{
    int nrChannels = 3;
    Worley W[3] = 
    {
        Worley(WR[0], WDH, WDH, WDH),
        Worley(WR[1], WDH, WDH, WDH),
        Worley(WR[2], WDH, WDH, WDH),
    };
    std::string path;
    if(name == "")
    {
        path =
        "./data/texture3D/WHD=" + std::to_string(WDH) +
        "_WR0=" + std::to_string(WR[0]) +
        "_WR1=" + std::to_string(WR[1]) +
        "_WR2=" + std::to_string(WR[2]) +
        ".3DT";
    }
    else
    {
        path = "./data/texture3D/" + name + ".3DT";
    }

    std::ofstream data(path, std::ios::out | std::ios::binary);
    
    if(!data.is_open())
    {
        std::cerr<<"Erreur ouverture fichier"<<std::endl;
        return false;
    }

    uint x, y, z;
    x = y = z = 0;
    uint i = 0;

  while(i < WDH * WDH * WDH * nrChannels)
    {
        unsigned char toFile[3] = {
        (unsigned char)(W[0].get3d(x, y, z) *  255),
        (unsigned char)(W[1].get3d(x, y, z) *  255),
        (unsigned char)(W[2].get3d(x, y, z) *  255)};
        writeTexture(data, toFile, 3);
        nextStepTexture(WDH, nrChannels, x, y, z, i);
    }
    data.write((char * )&WDH, sizeof(char));
    data.write((char * )&nrChannels, sizeof(char));
    data.close();
    return true;
}

bool Textures::Load3D(const std::string & key, const std::string & path)
{

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::ifstream file(path, std::ios::binary);
    if(!file.is_open())
    {
        std::cerr<<" Fichier Introuvable"<<std::endl;
        return false;
    }
    std::vector<unsigned char> data(std::istreambuf_iterator<char>(file), {});
    uint nChan = data.back();
    data.pop_back();
    uint WDH = data.back();
    data.pop_back();

    std::cout<<WDH<<std::endl;
    

    file.close();
    GLenum format = GL_RG;
    switch(nChan)
    {
        case 3: 
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
    }
    if(nChan == 4 )
    {
        format = GL_RGBA;
    }
    else if(nChan == 3)
    {
        format = GL_RGB;
    }
    
    std::cout<<data.size()/4<<std::endl;
    if(!data.empty())
    {
        
        m_texId.insert({key, 0});
        glGenTextures(1, &m_texId[key]);
        glBindTexture(GL_TEXTURE_3D, m_texId[key]);
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, WDH, WDH, WDH, 0, format, GL_UNSIGNED_BYTE, &data[0]);
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
