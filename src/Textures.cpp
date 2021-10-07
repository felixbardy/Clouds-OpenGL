#include "Textures.h"
Textures::Textures()
{

}

void Textures::initAtlas()
{
    glEnable(GL_TEXTURE_3D);
    //createAndLoad3D(m_blockAtlas);
    Load3D(m_blockAtlas, "./data/texture3D/suus.3DT");
    //loadTexture(nesCafey, "./data/coffeeSquare.jpg");
    //loadTexture(cage, "./data/Scage.jpg");

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
bool Textures::write3D4Chan(int WDH, int WR[3], int O, int S, int Fr, std::string name)
{
    int nrChannels = 4;
    FastNoise F;
    F.SetNoiseType(FastNoise::NoiseType::Perlin);
    F.SetSeed(S);
    F.SetFractalOctaves(O);
    F.SetFrequency((float)Fr/(float)100);

    //Worley W = Worley(WorleyRes, width, height, depth);

    Worley W[3] = 
    {
        Worley(WR[0], WDH, WDH, WDH),
        Worley(WR[1], WDH, WDH, WDH),
        Worley(WR[2], WDH, WDH, WDH),
    };

    std::ofstream data;
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
                                  "4CHAN\n"+
        std::to_string(WDH)          + "\n" +
        std::to_string(WR[0])       + "\n" +
        std::to_string(WR[1])       + "\n" +
        std::to_string(WR[2])       + "\n" +
        std::to_string(O)           + "\n" +    
        std::to_string(S)           + "\n" +
        std::to_string(Fr)          + "\n";

    data.write(option.c_str(), option.size());
    std::string str = "";
    while(i < WDH * WDH * WDH * nrChannels)
    {
        data
        <<(int)(((F.GetNoise(x, y, z) + 1)/2) * 255)<<" " // Injection Perlin
        <<(int)(W[0].get3d(x, y, z) *  255) << " "   // Injection Worley petite Res
        <<(int)(W[1].get3d(x, y, z) *  255) << " "   // Injection Worley moyenne Res 
        <<(int)(W[2].get3d(x, y, z) *  255) << " "   // Injection Worley grande Res
        <<std::endl;
        x++;
        if(x >= WDH)
        {
            x = 0;
            y++;
        }
        if(y >= WDH)
        {
            y = 0;
            z++;
            std::cout<<"Step : "<<z<<" / "<<WDH<<std::endl;
        }
        i+=nrChannels;
    }
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

bool Textures::write3D3Chan(int WDH, int WR[3], std::string name)
{
    int nrChannels = 3;

    Worley W[3] = 
    {
        Worley(WR[0], WDH, WDH, WDH),
        Worley(WR[1], WDH, WDH, WDH),
        Worley(WR[2], WDH, WDH, WDH),
    };

    std::ofstream data;
    std::string path;
    std::cout<<name<<std::endl;
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
                                  "3CHAN\n"+
        std::to_string(WDH)         + "\n" +
        std::to_string(WR[0])       + "\n" +
        std::to_string(WR[1])       + "\n" +
        std::to_string(WR[2])       + "\n";

    data.write(option.c_str(), option.size());
    std::string str = "";
    while(i < WDH * WDH * WDH * nrChannels)
    {
        data
        <<(int)(W[0].get3d(x, y, z) *  255) << " "   // Injection Worley petite Res
        <<(int)(W[1].get3d(x, y, z) *  255) << " "   // Injection Worley moyenne Res 
        <<(int)(W[2].get3d(x, y, z) *  255) << " "   // Injection Worley grande Res
        <<std::endl;
        x++;
        if(x >= WDH)
        {
            x = 0;
            y++;
        }
        if(y >= WDH)
        {
            y = 0;
            z++;
            std::cout<<"Step : "<<z<<" / "<<WDH<<std::endl;
        }
        i+=nrChannels;
    }
    data.close();
    return true;
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
    std::string line, type;
    getline(file, line);
    type = line;
    GLenum format = GL_RG;

   
    int nChan = 0;
    if(type == "4CHAN" )
    {
        nChan = 4;
        format = GL_RGBA;
    }
    else if(type == "3CHAN")
    {
        nChan = 3;
        format = GL_RGB;
    }


    getline(file, line);
    int WDH = std::stoi(line); // On recupere la largeur/hauteur/profondeur
    getline(file, line);
    int WR0 = std::stoi(line);
    getline(file, line);
    int WR1 = std::stoi(line);
    getline(file, line);
    int WR2 = std::stoi(line);

    if(type != "3CHAN")
    {
        getline(file, line);
        //int Octaves = std::stoi(line);
        getline(file, line);
        //int Seed = std::stoi(line);
        getline(file, line);
        //int Frequency = std::stoi(line);
        
    }
    line = "";
    int nbS = 0;
    while(std::getline(file, line))
    {
        int nbS = 0;
        int p,w0, w1, w2;
        if(type == "4CHAN")
        {
            while(file>>p>>w0>>w1>>w2)
            {
                data.push_back(p);
                data.push_back(w0);
                data.push_back(w1);
                data.push_back(w2);
            }
        }
        else if(type == "3CHAN")
        {
            while(file>>w0>>w1>>w2)
            {
                data.push_back(w0);
                data.push_back(w1);
                data.push_back(w2);
            }
        }
        

    }

    file.close();

    std::cout<<nbS<<std::endl;

    std::cout<<data.size()<<std::endl;
    if(!data.empty())
    {
        glGenTextures(1, &textures);
        glBindTexture(GL_TEXTURE_3D, textures);
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
