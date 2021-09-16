#ifndef DEF_ENGINE
#define DEF_ENGINE

#include <iostream>
#include "glad.h"
#include "Window.h"
#include "Shader.h"
#include "Textures.h"
#include "World.h"
#include <random>

using namespace glm;

/** @class Engine
 * @brief
 * 
 * Gère le rendu global
 * 
 */
class Engine
{
    public:

    World * zaWarudo;
    /** @brief Initialise les variables
     * @param vertexPath chemin vers le shader de vertex
     * @param fragmentPath chemin vers le shader de fragment
     */
    void init(std::string vertexPath, std::string fragmentPath, uint w = 500, uint h = 500);

    /** @brief Demarre le rendu      */
    void run();

    /** @brief fermer le rendu   */
    void close();
    /** @brief Change la couleur d'arrière plan
     * @param r valeur entre 0 et 1 de rouge
     * @param g valeur entre 0 et 1 de vert
     * @param b valeur entre 0 et 1 de bleue
     * @param a valeur entre 0 et 1 de transparence
     */
    void setBackgroundColor(float r, float g, float b, float a);

    /** @brief Accesseur adresse memoire shader */
    Shader* getShader();
    float lastTime = 0;
    Textures textureAltas;

    private:

    Window engineWindow;
    Shader shader;
    int inputPrevent;
    bool isWireframe = false;

    /** @brief Gère les inputs
     * @param Cam adresse memoire de la camera
     */
    void keyboardHandler(Camera * Cam);

    float r, g, b, a;

    int initGLAD();
};

#endif
