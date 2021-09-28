#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
/** @enum Movement
 * @brief
 * 
 * Gère les Direction pour déplacer la caméra
 * 
 */
enum Movement{FORWARD, BACKWARD, LEFT, RIGHT, UP, BOTTOM};

/** @class Camera
 * @brief
 * 
 * Gère une camera FPS avec sa matrice de view
 * 
 */
class Camera
{

public:
    /// @brief Constructeur par défaut
    Camera();

    /** @brief Constructeur par paramètre
     *  @param x position en x de la caméra
     *  @param y position en y de la caméra
     *  @param z position en z de la caméra
     */
    Camera(int x, int y, int z);

    glm::vec3 m_position; //!< Vecteur de position dans l'espace 
    glm::vec3 m_up;       //!< Vecteur d'axe Y pour le regard
    glm::vec3 m_right;    //!< Vecteur d'axe x pour le regard
    
    bool m_initMouse = true; /// Indique s'il faut initialiser la souris

    float m_yawD = -90.f; //!< Angle Euler Vertical
    float m_pitchD = 0.f; //!< Angle Euler Horizontal
    glm::vec3 m_front = glm::vec3(0.f, 0.f, -1.f);    //!< Vecteur de regard
    glm::vec3 m_frontMove = m_front;    //!< Vecteur de regard sans Y pour le déplacement (pour ne pas qu'il dépende de la hauteur)

    /** @brief accesseur référence matrice de vue
     *  @return reference matrice 4 dim
     */
    glm::mat4 & getViewRef();

    /** @brief accesseur matrice de vue
     * @return matrice 4 dim
     */
    glm::mat4 getView();


    /** @brief Actualise les vecteurs / matrice de la caméra
     */
    void update();

    /** @brief Accesseur vitesse
     *  @return float de la vitesse de déplacement
     */
    float getSpeed();

    /** @brief déplace la caméra dans l'espace
     *  @param m le type de déplacement
     *  @param speed vitesse de déplacement
     */
    void move(Movement m, float speed);

    /** @brief Accesseur position X souris précédente
     *  @return float
     */
    float getLastX();

    /** @brief Accesseur position Y souris précédente
     *  @return float
     */
    float getLastY();

    /** @brief Mutateur position X souris précédente
     *  @return float
     */
    void setLastX(float newX);

    /** @brief Mutateur position Y souris précédente
     *  @return float
     */
    void setLastY(float newY);

    /** @brief Affiche la matrice de vue en console     */
    void printView();

    /** @brief Accesseur sensibilité souris */
    float getMouseSensitivity();

    /** @brief Mutateur sensibilité souris
     *  @param newSensitivity
     */
    void setMouseSensitivity(float newSensitivity);

private:
    float m_lastX = 0;                   //!< Derniere position en X de la souris
    float m_lastY = 0;                   //!< Derniere position en Y de la souris
    float m_mouseSensitivity = 0.1f;  //!< Multiplicateur de sensibilité pour la souris
    /// matrice 4D de vue
    glm::mat4 m_view;
    /// Vitesse de déplacement de la caméra
    float m_speed = 10.f;


};

#endif //CAMERA_H
