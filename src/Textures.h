#ifndef TEXTURES_H
#define TEXTURES_H
#include <string>
#include <iostream>
#include "stb_image.h"
#include <vector>
#include "FastNoise.h"
#include "Worley.h"
#include <algorithm>
#include <map>

#include <fstream>

#include "lodepng.h"

#include "stb_image.h"
#include "glad.h"
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iomanip>
/** @class Textures
 * @brief Contient toutes les textures du projet
 * */
class Textures
{
    public:

    /** @brief Constructeur par défaut */
    Textures();

    /** @brief Destructeur par défaut */
    ~Textures();

    /** @brief Initialise toutes les textures */
    void init();

    void fillPoint(int width, int height, int x, int y, int z, FastNoise & F, Worley & W, std::vector<unsigned char> & tab);

    /** @brief Définit la texture a utiliser pour déssinner
     * @param texture uint contenant l'id de la texture
    */
    void use3D(const std::string& key, uint texNumb = 0);
    void use2D(const std::string& key, uint texNumb = 0);


    /** @brief Genere et charge une texture 3D dans la CG
     * @param texture uint qui va contenir l'ID de la texture
    */
    bool createAndLoad3D(const std::string& key);

    /** @brief Charge une texture 3D dans la CG
     * @param texture uint qui va contenir l'ID de la texture
     * @param path string qui contient le chemin de la texture
    */
    bool Load3D(const std::string & key, const std::string & path);
    void Load2D(const std::string & key, const std::string & path);
    

    /** @brief Ecrit une texture dans un fichier texte
     * @param path string qui contient le chemin du fichier ou écrire
    */
    bool write3D3Chan(int WDH, int WR[3], std::string name);
    bool write3D4Chan(int WDH, int WR[3], int O, int S, int F, std::string name);
    bool write2DCurl();

    

    void writeTexture(std::ofstream & file, unsigned char data[], const uint & length);
    void nextStepTexture(const uint & resolution, const uint & nChan, uint & x, uint & y, uint & z, uint & i);
    std::map<std::string, uint> m_texId;
    private:
    
};


#endif // TEXTURE_H
