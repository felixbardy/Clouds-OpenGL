#include "Textures.h"
Textures::Textures()
{

}




void Textures::initAtlas()
{
    glEnable(GL_TEXTURE_3D);
    //createAndLoad3D(m_blockAtlas);
    Load3D(m_blockAtlas, "./soos.3DT");
    //loadTexture(nesCafey, "./data/coffeeSquare.jpg");
    //loadTexture(cage, "./data/Scage.jpg");

}

bool Textures::write3D(int WDH, int WR, int O, int S, int Fr)
{
    int width, height, depth, nrChannels;
    width = height = depth = WDH;
    nrChannels = 2;
    int WorleyRes = WR;
    int Octaves = O;
    int Seed = S;
    int frequency = Fr;
    FastNoise F;
    F.SetNoiseType(FastNoise::NoiseType::Perlin);
    F.SetSeed(Seed);
    F.SetFractalOctaves(Octaves);
    F.SetFrequency((float)frequency/(float)100);
    
    Worley W = Worley(WorleyRes, width, height, depth);

    std::ofstream data;
    std::string path = 
    "WHD=" + std::to_string(width) + 
    "_WR=" + std::to_string(WorleyRes) + 
    "_O=" + std::to_string(Octaves) + 
    "_S=" + std::to_string(Seed)+ 
    "_F=" + std::to_string(frequency) + 
    ".3DT";

    data.open(path);
    if(!data.is_open())
    {
        std::cerr<<"Erreur ouverture fichier"<<std::endl;
        return false;
    }

    int x, y, z;
    x = y = z = 0;
    int i = 0;

    std::string option = 
        std::to_string(width)       + "\n" + 
        std::to_string(WorleyRes)   + "\n" + 
        std::to_string(Octaves)     + "\n" + 
        std::to_string(Seed)        + "\n" + 
        std::to_string(frequency)   + "\n";

    data.write(option.c_str(), option.size());
    std::string str = "";
    data<<std::fixed;
    data<<std::setprecision(16);
    while(i < width * depth * height * nrChannels)
    {
        data<<(((F.GetNoise(x, y, z) + 1)/2) * 255)<<" "<<(W.get3d(x, y, z) *  255)<<std::endl;
        //if(x % 16 == 0 && i != 0) data<<std::endl;
        

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
            std::cout<<"Step : "<<z<<" / "<<width<<std::endl;
        }
        i+=2;  
    }
    data.close();
    return true;
}

void Textures::use3D(const uint& texture)
{
    glBindTexture(GL_TEXTURE_3D, texture);
}

void Textures::fillPoint(int width, int height, int x, int y, int z, FastNoise & F, Worley & W, std::vector<unsigned char> & data)
{
    data.push_back(((F.GetNoise(x, y, z) + 1)/2) * 255);
    data.push_back(W.get3d(x, y, z) *  255);
}

bool Textures::createAndLoad3D(uint& textures)
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
    F.SetFrequency(0.15);
    
    Worley W = Worley(3, width, height, depth);

    std::vector<unsigned char> data;
    int x, y, z;
    x = y = z = 0;
    int i = 0;

    while(i < width * depth * height * nrChannels)
    {
        fillPoint(width, height, x, y, z, F, W, data);
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
            std::cout<<"step : "<<z<<" / "<<width<<std::endl;
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

bool Textures::Load3D(uint& textures, std::string path)
{
    
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::fstream file;

    
    file.open(path);
    
    if(!file.is_open())
    {
        std::cerr<<" Fichier Introuvable"<<std::endl;
        return false;
    }

    
    

    std::vector<unsigned char> data;
    std::string line;

    getline(file, line);
    int WDH = std::stoi(line);

    getline(file, line);
    int WR = std::stoi(line);
    getline(file, line);
    int O = std::stoi(line);
    getline(file, line);
    int S = std::stoi(line);
    getline(file, line);
    int F = std::stoi(line);

    line = "";

    std::string delimiter = ",";
    std::cout<<std::fixed;
    std::cout<<std::setprecision(32);
    
    int nbS = 0;
    while(std::getline(file, line))
    {
        
        
        int nbS = 0;
        float p,w;
        while(file>>p>>w)
        {
            data.push_back(p);
            data.push_back(w);
        }
        
    }

    file.close();

    std::cout<<nbS<<std::endl;

    std::cout<<data.size()<<std::endl;
    if(!data.empty())
    {
        glGenTextures(1, &textures);
        glBindTexture(GL_TEXTURE_3D, textures);
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, WDH, WDH, WDH, 0, GL_RG, GL_UNSIGNED_BYTE, &data[0]);
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
