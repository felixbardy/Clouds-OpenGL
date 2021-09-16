#ifndef DEF_WINDOW
#define DEF_WINDOW

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
/** @class Window
 * @brief Gestionnaire de la fenetre pour openGL
*/
class Window
{
    public:

    /** @brief Constructeur par défaut */
    Window();

    /** @brief Constructeur par argument
     * @param w largeur de la fenêtre
     * @param h hauteur de la fenêtre
     * @param title titre
    */
    Window(int w, int h, const std::string& title);

    /** @brief Destructeur par défaut */
    ~Window();

    /** @brief Initialisation de la fenêtre */
    int init();

    /** @brief Actualisation de la fenêtre */
    void update();
    bool quit = false;

    /** @brief Gestion des inputs */
    void keyboardHandler();

    /** @brief Accesseur pointeur de la fenêtre
     * @return Un poiteur vers une fenêtre GLFW
    */
    GLFWwindow* getWindow();

    /** @brief Accesseur largeur fenêtre
     * @return largeur
    */
    int getWidth();

    /** @brief Accesseur hauteur fenêtre
     * @return hauteur
    */
    int getHeight();


    private:

    int width, height;
    std::string title;
    GLFWwindow* window;

    double xPos, yPos;


    /** @brief Initialisation de la librairie GLFW
     * @param major version d'openGL (genre 1 2 3 4)
     * @param minor petite version d'openGL (genre le 5 de 4.5)
     * @return -1 en cas d'erreur
    */
    int initGlfw(const int & major = 4, const int & minor = 5);

    /** @brief Initialisation du pointeur d ela fenêtre
     * @return -1 en cas d'erreur
    */
    int initWindow();

    /** @brief Initialisation de la librairie GLAD
     * @return -1 en cas d'erreur
    */
    int initGLAD();




};

#endif
