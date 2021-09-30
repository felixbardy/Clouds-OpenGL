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
     * @param shaderToUse Pointeur vers le shader a utiliser
     * @param projection matrice 4 dimension du monde
     * @param view matrice 4 dimension de vue
     */
    void draw(Shader * shaderToUse, glm::mat4& projection, glm::mat4& view);

    /** @brief affiche le mesh
     * @param angle angle de rotation
     * @param shaderToUse Pointeur vers le shader a utiliser
     * @param projection matrice 4 dimension du monde
     * @param view matrice 4 dimension de vue
     */
    void render(float angle, Shader & Shader, glm::mat4 & projection, glm::mat4 & view);

    /** @brief remplit les positions ou afficher le mesh
     * @param positions
     */
    void setPosition(std::vector<glm::vec3> positions);

    /** @brief remplit les vertices du mesh
     * @param texture texture du jeu
     * @param vertexArray Vecteur contenant toutes les vertices
     * @param u Vecteur contenant toutes les uv
     * @param uvIndex Vecteur contenant les indices de l'odre ou utiliser les uvs
     * @param c vecteur de couleur
     * @param indiceArray indices de l'ordre ou utiliser les vertices
     * @param id id du block a afficher
     */
    void setPolygon(const Textures& texture, std::vector<float> vertexArray, std::vector<float> u, std::vector<uint> uvIndex, std::vector<float> c, std::vector<uint> indicesArray, uint id);
    
    /** @brief remplit les vertices du Cube
     * @param texture texture du jeu
     * @param id id du block a afficher
     * @param u Vecteur contenant toutes les uv
     * @param uvIndex Vecteur contenant les indices de l'odre ou utiliser les uvs
     * @param c vecteur de couleur
     */
    void setCube(const Textures & texture, uint id = 0, std::vector<float> u = {},  std::vector<uint> uI = {}, std::vector<float> c = {});
     
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
