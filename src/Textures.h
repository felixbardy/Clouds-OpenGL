#ifndef DEF_TEXTURES
#define DEF_TEXTURES
#include <string>
#include <iostream>
#include "stb_image.h"
#include <vector>
#include "FastNoise.h"
#include <thread>
#include <mutex>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

    std::mutex m;

    float worley(glm::vec3 position);

    void fillPoint(int width, int height, int i, int x, int y, int z, FastNoise & F, std::vector<unsigned char> & tab);

    /** @brief Définit la texture a utiliser pour déssinner
     * @param texture uint contenant l'id de la texture
    */
    void useTexture(const uint& texture);
    
    /// Variable de référence de la texture blockAtlas
    uint blockAtlas;
    /// Variable de référence de Nescafey, what else ?
    uint nesCafey;
    /// Valeur de référence de la texture de nicolas cage
    uint cage;
    uint tex3D;
    /** @brief Charge une texture dans la CG
     * @param texture uint qui va contenir l'ID de la texture
     * @param path string qui contient le chemin de la texture
    */
    bool loadTexture(uint& texture, std::string path);

    /// Tableau des id des textures pour les faces des cubes minecraft
    std::vector<std::vector<uint>> blockTextures =
    {
        {0, 0, 0, 0, 0, 0}, //Stone
        {5, 5, 5, 5, 6, 6}, // Oak Log
        {10, 10, 10, 10, 10, 10}, //Sand DEV DER G D H B
        {12, 13, 13, 13, 15, 15}
    };




    private:

};


#endif
