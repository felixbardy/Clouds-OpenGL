#ifndef TEXTURES_H
#define TEXTURES_H
#include <string>
#include <iostream>
#include "stb_image.h"
#include <vector>
#include "FastNoise.h"
#include "Worley.h"
#include <algorithm>

#include <fstream>

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
    void initAtlas();

    void fillPoint(int width, int height, int x, int y, int z, FastNoise & F, Worley & W, std::vector<unsigned char> & tab);

    /** @brief Définit la texture a utiliser pour déssinner
     * @param texture uint contenant l'id de la texture
    */
    void use3D(const uint& texture);


    /** @brief Genere et charge une texture 3D dans la CG
     * @param texture uint qui va contenir l'ID de la texture
    */
    bool createAndLoad3D(uint& textures);

    /** @brief Charge une texture 3D dans la CG
     * @param texture uint qui va contenir l'ID de la texture
     * @param path string qui contient le chemin de la texture
    */
    bool Load3D(uint& textures, std::string path);

    /** @brief Ecrit une texture dans un fichier texte
     * @param path string qui contient le chemin du fichier ou écrire
    */
    bool write3D3Chan(int WDH, int WR[3], std::string name);
    bool write3D4Chan(int WDH, int WR[3], int O, int S, int F, std::string name);
    bool write3DCurl();
    /// Variable de référence de la texture blockAtlas
    uint m_blockAtlas;
    /// Variable de référence de Nescafey, what else ?
    uint m_nesCafey;
    /// Valeur de référence de la texture de nicolas cage
    uint m_cage;
    uint m_tex3D;
    
   

    private:

};


#endif // TEXTURE_H
