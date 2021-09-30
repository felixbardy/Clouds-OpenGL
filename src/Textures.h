#ifndef DEF_TEXTURES
#define DEF_TEXTURES
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

		/** @brief Charge une texture dans la CG
     * @param texture uint qui va contenir l'ID de la texture
     * @param path string qui contient le chemin de la texture
    */
		bool loadTexture(std::string path);
		bool generate3DWorley();

    void fillPoint(int width, int height, int x, int y, int z, FastNoise & F, Worley & W, std::vector<unsigned char> & tab);

    /** @brief Définit la texture a utiliser pour déssinner
     * @param texture uint contenant l'id de la texture
    */
    void use3D(const uint& texture);
		void useTexture();

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
    bool write3D(int WDH, int WR, int O, int S, int F, std::string name);


    uint texUint;


    private:

};


#endif
