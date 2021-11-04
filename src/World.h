
#ifndef WORLD_H
#define WORLD_H

#include "Camera.h"
#include "Objects.h"

/** @class World
 * @brief Gère les meshs, un peu comme une scène sur unity et contient la matrice du monde
 */
class World
{
    public:

    /// Tableau dynamique des meshs de la scène
    std::vector<Object *> m_objects;
    /// Pointeur vers la caméra utilisée pour afficher la scène
    Camera * m_cam;
    /// Matrice de projection utilisée
    glm::mat4 m_projection;

    /** @brief Ajoute un cube a la scene
     * @param textures Les textures à appliquer au mesh 
     */
    void addNewCube(const std::string & shaderKey, std::vector<std::string> textureKeys, bool is2D = false);

    Camera* getCam();
    
    /** @brief Ajoute un cube a la scene
     * @param textures Les textures à appliquer au mesh 
     */
    void addObject(Object * obj);

    /** @brief Affiche la scène sur le contexte courant avec le shader et temps fournis
     * @param Shader les shaders à utiliser
     * @param time le temps actuel du monde
     */
    void render(Shader & shaderManager, Textures & textureManager, float time);

    /** @brief Fait la mise à jour physique du monde
     */
    void update();

    /** @brief Constructeur par défaut, initialise la caméra et la matrice de projection
     */
    World();

    /// 
    /** @brief Destructeur, détruit la caméra et les meshs avant l'objet
     */
    ~World();


};

#endif // WORLD_H
