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

    /// Pointeur vers le MONDEUH
    World * m_world;

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

    /// Temps de la dernière frame
    float m_lastTime = 0;

    /// Instance de l'objet contenant toutes les textures
    Textures m_textureAltas;

private:
    
    Window m_engineWindow;        //!< Instance de l'objet contenant la fenêtre
    Shader m_shader;              //!< Instance du shader
    int m_inputPrevent;           //!< Variable de prévetion pour éviter les multiples input
    bool m_isWireframe = false;   //!< Booléen, si oui le rendu passe en wireframe
    bool m_isCursorLocked = true; //!< Booléen, si non le curseur n'est plus bloqué par la fenêtre
    bool m_isFullscreen = false;  //!< Indique si la fenêtre est en plein écran

    /** @brief Gère les inputs
     * @param cam adresse memoire de la camera
     */
    void keyboardHandler(Camera * cam);

    float r; //!< Valeur de rouge du background entre 0 et 1
    float g; //!< Valeur de vert du background entre 0 et 1
    float b; //!< Valeur de bleue du background entre 0 et 1
    float a; //!< Valeur de transparence du background entre 0 et 1

    /** @brief Initialise GLAD */
    int initGLAD();
};

#endif
