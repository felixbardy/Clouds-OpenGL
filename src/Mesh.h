#ifndef MESH_H
#define MESH_H







#include "glad.h"
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Textures.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/** @class Mesh
 * @brief Genere un maillage utilisable par openGL */

class Mesh
{
    public:
    /** @brief Constructeur par défaut     */
    Mesh();

    /** @brief destructeur par défaut     */
    ~Mesh();

    /** @brief Tourne autour des axes données
     * @param angle Angle de la rotation
     * @param vAxis axes
     */
    void rotate(float angle, glm::vec3 vAxis);

    /** @brief Redimensionne sur les axes le mesh
     * @param vScale vecteur de redimensionnement
     */
    void scale(glm::vec3 vScale);

    /** @brief Déplace du vecteur donnée en paramètre dans le monde
     * @param vTranslate vecteur de translation
     */
    void translate(glm::vec3 vTranslate);

    /** @brief Dessinne le mesh
     */
    void draw();

    /** @brief affiche le mesh
     * @param angle angle de rotation
     * @param shaderToUse Pointeur vers le shader a utiliser
     * @param projection matrice 4 dimension du monde
     * @param view matrice 4 dimension de vue
     */
    void render(Shader & Shader, Textures & textureManager, const glm::mat4 & view, const glm::mat4 & projection, float angle);

    /** @brief remplit les positions ou afficher le mesh
     * @param positions
     */
    void setPosition(std::vector<glm::vec3> positions);

    /** @brief remplit la clé du shader du mesh
     * @param key
     */
    void setShaderKey(const std::string & shaderKey);

    /** @brief remplit la clé du shader du mesh
     * @param keys vecteur de string
     */
    void setTextureKeys(std::vector<std::string> keys);

      /** @brief obtient la clé du shader du mesh
     * @param key
     */
    std::string getShaderKey();

    void setTextureTypeTo3D();
    void setTextureTypeTo2D();

    /** @brief remplit les vertices du mesh
     * @param vertexArray Vecteur contenant toutes les vertices
     * @param u Vecteur contenant toutes les uv
     * @param uvIndex Vecteur contenant les indices de l'odre ou utiliser les uvs
     * @param c vecteur de couleur
     * @param indiceArray indices de l'ordre ou utiliser les vertices
     */
    void setPolygon(std::vector<float> vertices, std::vector<uint> verticesOrder, std::vector<float> uvArray = {}, std::vector<uint> uvOrder = {}, std::vector<float> color = {}, std::vector<uint> colorOrder = {});
    
    /** @brief remplit les vertices du Cube
     * @param u Vecteur contenant toutes les uv
     * @param uvIndex Vecteur contenant les indices de l'odre ou utiliser les uvs
     * @param c vecteur de couleur
     */
    void setCube();
     
    /** @brief retire les transformation     */
    void resetModel();

    /** @brief Accesseur Vertex Array Object
     * @return id uint de l'objet
    */
    uint & getVAO();

    

    /** @brief init le mesh    */
    void init();

    /// Matrice 4D de repère de l'objet
    glm::mat4 m_model;
    /// Vecteur 3D de position
    std::vector<glm::vec3> m_position;
    /// Vecteur d'indices des sommets
    std::vector<uint> m_indices;

    private:

    /// Tableau des vertexs à déssinner
    std::vector<float> m_vertex;

    std::string m_shaderKey;
    std::vector<std::string> m_texturesKeys;
    bool is2D = false;

    /// Variable de référence du Vertex Array Object
    unsigned int m_VAO;

    /// Variable de référence du Vertex Buffer Object
    unsigned int m_VBO;

    /// Variable de référence de l'Element Buffer Object
    unsigned int m_EBO;

    /** @brief init le Vertex Buffer Object    */
    void initVBO();
    /** @brief init le Vertex Array Object    */
    void initVAO();
    /** @brief init le Element Buffer Object    */
    void initEBO();

};

#endif //MESH_H
