#ifndef WINDOW_H
#define WINDOW_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/** @class Window
 * @brief Gestionnaire de la fenetre pour openGL
*/
class Window
{
    public:

    void beginGui(const std::string & Title);
    void endGui();
    void drawGui();


    void slider(const std::string & title, float & f, float min, float max);
    bool button(const std::string & title, float width, float height);
    void checkBox(const std::string & title, bool & value);

    /// Booléen de quittage de rendue
    bool m_quit = false;

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

    /// Largeur de la fenêtre
    int m_width;
    /// Hauteur de la fenêtre
    int m_height;

    /// Titre de la fenêtre
    std::string m_title;

    /// Pointeur GLFW de la fenêtre
    GLFWwindow* m_window;

    /// Position X de la souris
    double m_xPos;
    /// Position Y de la souris
    double m_yPos;

    ImGuiIO * m_IO = new ImGuiIO;

    void initImGui();

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

#endif // WINDOW_H
