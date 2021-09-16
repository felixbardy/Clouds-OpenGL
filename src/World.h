
#ifndef DEF_WORLD
#define DEF_WORLD

#include "Camera.h"
#include "Mesh.h"

/// @TODO écrire la doc de World
/** @class World
 * @brief
 * 
 * Gère les meshs, un peu comme une scène sur unity et contient la matrice du monde
 * 
 */
class World
{
    public:

    /// Tableau dynamique des meshs de la scène
    std::vector<Mesh *> Meshs;
    /// Pointeur vers la caméra utilisée pour afficher la scène
    Camera * Cam;
    /// Matrice de projection utilisée
    glm::mat4 projection;

    /** @brief Ajoute un mesh à la scène
     * @param textures Les textures à appliquer au mesh 
     */
    void addMesh(const Textures& textures);

    /** @brief Affiche la scène sur le contexte courant avec le shader et temps fournis
     * @param Shader les shaders à utiliser
     * @param time le temps actuel du monde
     */
    void render(Shader & Shader, float time);

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

#endif
