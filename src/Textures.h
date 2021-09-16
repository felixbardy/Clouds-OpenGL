#ifndef DEF_TEXTURES
#define DEF_TEXTURES
#include <string>
#include <iostream>
#include "stb_image.h"
#include <vector>
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

    /** @brief Définit la texture a utiliser pour déssinner
     * @param texture uint contenant l'id de la texture
    */
    void useTexture(const uint& texture);
    
    uint blockAtlas;
    uint nesCafey;
    uint cage;

    /** @brief Charge une texture dans la CG
     * @param texture uint qui va contenir l'ID de la texture
     * @param path string qui contient le chemin de la texture
    */
    bool loadTexture(uint& texture, std::string path);

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
