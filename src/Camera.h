#ifndef DEF_CAMERA
#define DEF_CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
/** @enum movement
 * @brief
 * 
 * Gère les Direction pour déplacer la caméra
 * 
 */
enum movement{FORWARD, BACKWARD, LEFT, RIGHT, UP, BOTTOM};

/** @class Camera
 * @brief
 * 
 * Gère une camera FPS avec sa matrice de view
 * 
 */
class Camera
{
    public:

    /** @brief accesseur référence matrice de vue
     *  @return reference matrice 4 dim
     */
    glm::mat4 & getViewRef();

    /** @brief accesseur matrice de vue
     * @return matrice 4 dim
     */
    glm::mat4 getView();

    /** @brief Constructeur par paramètre
     *  @param x position en x de la caméra
     *  @param y position en y de la caméra
     *  @param z position en z de la caméra
     */
    Camera(int x, int y, int z);

    /// @brief Constructeur par défaut
    Camera();

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
    void move(movement m, float speed);

    /// Vecteur de position dans l'espace 
    glm::vec3 position;

    /// Vecteur d'axe Y pour le regard
    glm::vec3 up;

    /// Vecteur d'axe x pour le regard
    glm::vec3 right;

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

    /// Vrai si il faut initialisé la souris
    bool initMouse = true;

    /// Angle Euler Vertical
    float yawD = -90.f;

    /// Angle Euler Horizontal
    float pitchD = 0.f;

    /// Vecteur de regard
    glm::vec3 front = glm::vec3(0.f, 0.f, -1.f);

    /// Vecteur de regard sans Y pour le déplacement (pour ne pas qu'il dépende de la hauteur)
    glm::vec3 frontMove = front;

    private:

    /// Derniere position en X de la souris
    float lX = 0;

    /// Derniere position en Y de la souris
    float lY = 0;

    /// Multiplicateur de sensibilité pour la souris
    float mouseSensitivity = 0.1f;

    /// matrice 4D de vue
    glm::mat4 view;

    /// Vitesse de déplacement
    float speed = 3.f;

};

#endif
